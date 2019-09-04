#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct pci_dev {int /*<<< orphan*/  dev; } ;
struct cxl_afu {int /*<<< orphan*/  current_mode; } ;
struct cxl {int slices; int /*<<< orphan*/  contexts_num; int /*<<< orphan*/  dev; int /*<<< orphan*/  afu_list_lock; struct cxl_afu** afu; int /*<<< orphan*/  perst_same_image; scalar_t__ perst_loads_image; } ;
typedef  scalar_t__ pci_ers_result_t ;
typedef  int /*<<< orphan*/  pci_channel_state_t ;
struct TYPE_2__ {int /*<<< orphan*/  (* afu_deactivate_mode ) (struct cxl_afu*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 scalar_t__ PCI_ERS_RESULT_DISCONNECT ; 
 scalar_t__ PCI_ERS_RESULT_NEED_RESET ; 
 scalar_t__ PCI_ERS_RESULT_NONE ; 
 int /*<<< orphan*/  atomic_read (int /*<<< orphan*/ *) ; 
 scalar_t__ cxl_adapter_context_lock (struct cxl*) ; 
 int /*<<< orphan*/  cxl_context_detach_all (struct cxl_afu*) ; 
 int /*<<< orphan*/  cxl_deconfigure_adapter (struct cxl*) ; 
 TYPE_1__* cxl_ops ; 
 scalar_t__ cxl_vphb_error_detected (struct cxl_afu*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_channel_io_perm_failure ; 
 int /*<<< orphan*/  pci_deconfigure_afu (struct cxl_afu*) ; 
 struct cxl* pci_get_drvdata (struct pci_dev*) ; 
 int /*<<< orphan*/  schedule () ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct cxl_afu*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static pci_ers_result_t cxl_pci_error_detected(struct pci_dev *pdev,
					       pci_channel_state_t state)
{
	struct cxl *adapter = pci_get_drvdata(pdev);
	struct cxl_afu *afu;
	pci_ers_result_t result = PCI_ERS_RESULT_NEED_RESET;
	pci_ers_result_t afu_result = PCI_ERS_RESULT_NEED_RESET;
	int i;

	/* At this point, we could still have an interrupt pending.
	 * Let's try to get them out of the way before they do
	 * anything we don't like.
	 */
	schedule();

	/* If we're permanently dead, give up. */
	if (state == pci_channel_io_perm_failure) {
		spin_lock(&adapter->afu_list_lock);
		for (i = 0; i < adapter->slices; i++) {
			afu = adapter->afu[i];
			/*
			 * Tell the AFU drivers; but we don't care what they
			 * say, we're going away.
			 */
			cxl_vphb_error_detected(afu, state);
		}
		spin_unlock(&adapter->afu_list_lock);
		return PCI_ERS_RESULT_DISCONNECT;
	}

	/* Are we reflashing?
	 *
	 * If we reflash, we could come back as something entirely
	 * different, including a non-CAPI card. As such, by default
	 * we don't participate in the process. We'll be unbound and
	 * the slot re-probed. (TODO: check EEH doesn't blindly rebind
	 * us!)
	 *
	 * However, this isn't the entire story: for reliablity
	 * reasons, we usually want to reflash the FPGA on PERST in
	 * order to get back to a more reliable known-good state.
	 *
	 * This causes us a bit of a problem: if we reflash we can't
	 * trust that we'll come back the same - we could have a new
	 * image and been PERSTed in order to load that
	 * image. However, most of the time we actually *will* come
	 * back the same - for example a regular EEH event.
	 *
	 * Therefore, we allow the user to assert that the image is
	 * indeed the same and that we should continue on into EEH
	 * anyway.
	 */
	if (adapter->perst_loads_image && !adapter->perst_same_image) {
		/* TODO take the PHB out of CXL mode */
		dev_info(&pdev->dev, "reflashing, so opting out of EEH!\n");
		return PCI_ERS_RESULT_NONE;
	}

	/*
	 * At this point, we want to try to recover.  We'll always
	 * need a complete slot reset: we don't trust any other reset.
	 *
	 * Now, we go through each AFU:
	 *  - We send the driver, if bound, an error_detected callback.
	 *    We expect it to clean up, but it can also tell us to give
	 *    up and permanently detach the card. To simplify things, if
	 *    any bound AFU driver doesn't support EEH, we give up on EEH.
	 *
	 *  - We detach all contexts associated with the AFU. This
	 *    does not free them, but puts them into a CLOSED state
	 *    which causes any the associated files to return useful
	 *    errors to userland. It also unmaps, but does not free,
	 *    any IRQs.
	 *
	 *  - We clean up our side: releasing and unmapping resources we hold
	 *    so we can wire them up again when the hardware comes back up.
	 *
	 * Driver authors should note:
	 *
	 *  - Any contexts you create in your kernel driver (except
	 *    those associated with anonymous file descriptors) are
	 *    your responsibility to free and recreate. Likewise with
	 *    any attached resources.
	 *
	 *  - We will take responsibility for re-initialising the
	 *    device context (the one set up for you in
	 *    cxl_pci_enable_device_hook and accessed through
	 *    cxl_get_context). If you've attached IRQs or other
	 *    resources to it, they remains yours to free.
	 *
	 * You can call the same functions to release resources as you
	 * normally would: we make sure that these functions continue
	 * to work when the hardware is down.
	 *
	 * Two examples:
	 *
	 * 1) If you normally free all your resources at the end of
	 *    each request, or if you use anonymous FDs, your
	 *    error_detected callback can simply set a flag to tell
	 *    your driver not to start any new calls. You can then
	 *    clear the flag in the resume callback.
	 *
	 * 2) If you normally allocate your resources on startup:
	 *     * Set a flag in error_detected as above.
	 *     * Let CXL detach your contexts.
	 *     * In slot_reset, free the old resources and allocate new ones.
	 *     * In resume, clear the flag to allow things to start.
	 */

	/* Make sure no one else changes the afu list */
	spin_lock(&adapter->afu_list_lock);

	for (i = 0; i < adapter->slices; i++) {
		afu = adapter->afu[i];

		if (afu == NULL)
			continue;

		afu_result = cxl_vphb_error_detected(afu, state);
		cxl_context_detach_all(afu);
		cxl_ops->afu_deactivate_mode(afu, afu->current_mode);
		pci_deconfigure_afu(afu);

		/* Disconnect trumps all, NONE trumps NEED_RESET */
		if (afu_result == PCI_ERS_RESULT_DISCONNECT)
			result = PCI_ERS_RESULT_DISCONNECT;
		else if ((afu_result == PCI_ERS_RESULT_NONE) &&
			 (result == PCI_ERS_RESULT_NEED_RESET))
			result = PCI_ERS_RESULT_NONE;
	}
	spin_unlock(&adapter->afu_list_lock);

	/* should take the context lock here */
	if (cxl_adapter_context_lock(adapter) != 0)
		dev_warn(&adapter->dev,
			 "Couldn't take context lock with %d active-contexts\n",
			 atomic_read(&adapter->contexts_num));

	cxl_deconfigure_adapter(adapter);

	return result;
}
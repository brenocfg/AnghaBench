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
struct cxl_afu {int dummy; } ;
struct cxl {int slices; int /*<<< orphan*/  afu_list_lock; struct cxl_afu** afu; TYPE_1__* guest; } ;
struct TYPE_2__ {int /*<<< orphan*/  handle; } ;

/* Variables and functions */
 int /*<<< orphan*/  CXL_ERROR_DETECTED_EVENT ; 
 int /*<<< orphan*/  CXL_RESUME_EVENT ; 
 int /*<<< orphan*/  CXL_SLOT_RESET_EVENT ; 
 int /*<<< orphan*/  cxl_context_detach_all (struct cxl_afu*) ; 
 int cxl_h_reset_adapter (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_channel_io_frozen ; 
 int /*<<< orphan*/  pci_channel_io_normal ; 
 int /*<<< orphan*/  pci_error_handlers (struct cxl_afu*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_devel (char*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int guest_reset(struct cxl *adapter)
{
	struct cxl_afu *afu = NULL;
	int i, rc;

	pr_devel("Adapter reset request\n");
	spin_lock(&adapter->afu_list_lock);
	for (i = 0; i < adapter->slices; i++) {
		if ((afu = adapter->afu[i])) {
			pci_error_handlers(afu, CXL_ERROR_DETECTED_EVENT,
					pci_channel_io_frozen);
			cxl_context_detach_all(afu);
		}
	}

	rc = cxl_h_reset_adapter(adapter->guest->handle);
	for (i = 0; i < adapter->slices; i++) {
		if (!rc && (afu = adapter->afu[i])) {
			pci_error_handlers(afu, CXL_SLOT_RESET_EVENT,
					pci_channel_io_normal);
			pci_error_handlers(afu, CXL_RESUME_EVENT, 0);
		}
	}
	spin_unlock(&adapter->afu_list_lock);
	return rc;
}
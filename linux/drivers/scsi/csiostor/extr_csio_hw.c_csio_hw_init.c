#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct TYPE_4__ {int /*<<< orphan*/  device_id; int /*<<< orphan*/  vendor_id; } ;
struct TYPE_5__ {scalar_t__ log_level; TYPE_1__ pci; } ;
struct TYPE_6__ {int /*<<< orphan*/  sm_list; } ;
struct csio_hw {int /*<<< orphan*/  dev_num; int /*<<< orphan*/  evt_free_q; int /*<<< orphan*/  evt_active_q; TYPE_2__ params; int /*<<< orphan*/ * chip_ops; int /*<<< orphan*/  name; int /*<<< orphan*/  sln_head; int /*<<< orphan*/  lock; TYPE_3__ sm; } ;
struct csio_evt_msg {int /*<<< orphan*/  list; } ;

/* Variables and functions */
 int /*<<< orphan*/  CSIO_HW_NAME ; 
 int /*<<< orphan*/  CSIO_INC_STATS (struct csio_hw*,int /*<<< orphan*/ ) ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 scalar_t__ csio_dbg_level ; 
 int /*<<< orphan*/  csio_err (struct csio_hw*,char*) ; 
 int /*<<< orphan*/  csio_evtq_cleanup (struct csio_hw*) ; 
 scalar_t__ csio_evtq_sz ; 
 int /*<<< orphan*/  csio_hw_get_device_id (struct csio_hw*) ; 
 int /*<<< orphan*/  csio_hw_mb_timer ; 
 int /*<<< orphan*/  csio_hw_set_description (struct csio_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  csio_hw_to_mbm (struct csio_hw*) ; 
 int /*<<< orphan*/  csio_hw_to_mgmtm (struct csio_hw*) ; 
 int /*<<< orphan*/  csio_hw_to_scsim (struct csio_hw*) ; 
 int /*<<< orphan*/  csio_hw_to_wrm (struct csio_hw*) ; 
 int /*<<< orphan*/  csio_hws_uninit ; 
 int /*<<< orphan*/  csio_init_state (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  csio_mbm_exit (int /*<<< orphan*/ ) ; 
 scalar_t__ csio_mbm_init (int /*<<< orphan*/ ,struct csio_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  csio_mgmtm_exit (int /*<<< orphan*/ ) ; 
 int csio_mgmtm_init (int /*<<< orphan*/ ,struct csio_hw*) ; 
 int /*<<< orphan*/  csio_scsim_exit (int /*<<< orphan*/ ) ; 
 int csio_scsim_init (int /*<<< orphan*/ ,struct csio_hw*) ; 
 int /*<<< orphan*/  csio_set_fwevt_intr_idx (struct csio_hw*,int) ; 
 int /*<<< orphan*/  csio_set_nondata_intr_idx (struct csio_hw*,int) ; 
 int /*<<< orphan*/  csio_wrm_exit (int /*<<< orphan*/ ,struct csio_hw*) ; 
 int csio_wrm_init (int /*<<< orphan*/ ,struct csio_hw*) ; 
 int /*<<< orphan*/  dev_num ; 
 struct csio_evt_msg* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  n_evt_freeq ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  t5_ops ; 

int
csio_hw_init(struct csio_hw *hw)
{
	int rv = -EINVAL;
	uint32_t i;
	uint16_t ven_id, dev_id;
	struct csio_evt_msg	*evt_entry;

	INIT_LIST_HEAD(&hw->sm.sm_list);
	csio_init_state(&hw->sm, csio_hws_uninit);
	spin_lock_init(&hw->lock);
	INIT_LIST_HEAD(&hw->sln_head);

	/* Get the PCI vendor & device id */
	csio_hw_get_device_id(hw);

	strcpy(hw->name, CSIO_HW_NAME);

	/* Initialize the HW chip ops T5 specific ops */
	hw->chip_ops = &t5_ops;

	/* Set the model & its description */

	ven_id = hw->params.pci.vendor_id;
	dev_id = hw->params.pci.device_id;

	csio_hw_set_description(hw, ven_id, dev_id);

	/* Initialize default log level */
	hw->params.log_level = (uint32_t) csio_dbg_level;

	csio_set_fwevt_intr_idx(hw, -1);
	csio_set_nondata_intr_idx(hw, -1);

	/* Init all the modules: Mailbox, WorkRequest and Transport */
	if (csio_mbm_init(csio_hw_to_mbm(hw), hw, csio_hw_mb_timer))
		goto err;

	rv = csio_wrm_init(csio_hw_to_wrm(hw), hw);
	if (rv)
		goto err_mbm_exit;

	rv = csio_scsim_init(csio_hw_to_scsim(hw), hw);
	if (rv)
		goto err_wrm_exit;

	rv = csio_mgmtm_init(csio_hw_to_mgmtm(hw), hw);
	if (rv)
		goto err_scsim_exit;
	/* Pre-allocate evtq and initialize them */
	INIT_LIST_HEAD(&hw->evt_active_q);
	INIT_LIST_HEAD(&hw->evt_free_q);
	for (i = 0; i < csio_evtq_sz; i++) {

		evt_entry = kzalloc(sizeof(struct csio_evt_msg), GFP_KERNEL);
		if (!evt_entry) {
			rv = -ENOMEM;
			csio_err(hw, "Failed to initialize eventq");
			goto err_evtq_cleanup;
		}

		list_add_tail(&evt_entry->list, &hw->evt_free_q);
		CSIO_INC_STATS(hw, n_evt_freeq);
	}

	hw->dev_num = dev_num;
	dev_num++;

	return 0;

err_evtq_cleanup:
	csio_evtq_cleanup(hw);
	csio_mgmtm_exit(csio_hw_to_mgmtm(hw));
err_scsim_exit:
	csio_scsim_exit(csio_hw_to_scsim(hw));
err_wrm_exit:
	csio_wrm_exit(csio_hw_to_wrm(hw), hw);
err_mbm_exit:
	csio_mbm_exit(csio_hw_to_mbm(hw));
err:
	return rv;
}
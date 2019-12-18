#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */

/* Variables and functions */
 int /*<<< orphan*/  _scsih_done ; 
 int /*<<< orphan*/  _scsih_io_done ; 
 int /*<<< orphan*/  _scsih_sas_control_complete ; 
 int /*<<< orphan*/  _scsih_tm_done ; 
 int /*<<< orphan*/  _scsih_tm_tr_complete ; 
 int /*<<< orphan*/  _scsih_tm_volume_tr_complete ; 
 void* base_cb_idx ; 
 void* config_cb_idx ; 
 void* ctl_cb_idx ; 
 scalar_t__ mpt2_ids ; 
 scalar_t__ mpt3_ids ; 
 int /*<<< orphan*/  mpt3sas_base_done ; 
 int /*<<< orphan*/  mpt3sas_base_initialize_callback_handler () ; 
 void* mpt3sas_base_register_callback_handler (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mpt3sas_config_done ; 
 int /*<<< orphan*/  mpt3sas_ctl_done ; 
 int /*<<< orphan*/  mpt3sas_port_enable_done ; 
 int /*<<< orphan*/  mpt3sas_transport_done ; 
 void* port_enable_cb_idx ; 
 void* scsi_io_cb_idx ; 
 void* scsih_cb_idx ; 
 void* tm_cb_idx ; 
 void* tm_sas_control_cb_idx ; 
 void* tm_tr_cb_idx ; 
 void* tm_tr_volume_cb_idx ; 
 void* transport_cb_idx ; 

__attribute__((used)) static int
scsih_init(void)
{
	mpt2_ids = 0;
	mpt3_ids = 0;

	mpt3sas_base_initialize_callback_handler();

	 /* queuecommand callback hander */
	scsi_io_cb_idx = mpt3sas_base_register_callback_handler(_scsih_io_done);

	/* task management callback handler */
	tm_cb_idx = mpt3sas_base_register_callback_handler(_scsih_tm_done);

	/* base internal commands callback handler */
	base_cb_idx = mpt3sas_base_register_callback_handler(mpt3sas_base_done);
	port_enable_cb_idx = mpt3sas_base_register_callback_handler(
	    mpt3sas_port_enable_done);

	/* transport internal commands callback handler */
	transport_cb_idx = mpt3sas_base_register_callback_handler(
	    mpt3sas_transport_done);

	/* scsih internal commands callback handler */
	scsih_cb_idx = mpt3sas_base_register_callback_handler(_scsih_done);

	/* configuration page API internal commands callback handler */
	config_cb_idx = mpt3sas_base_register_callback_handler(
	    mpt3sas_config_done);

	/* ctl module callback handler */
	ctl_cb_idx = mpt3sas_base_register_callback_handler(mpt3sas_ctl_done);

	tm_tr_cb_idx = mpt3sas_base_register_callback_handler(
	    _scsih_tm_tr_complete);

	tm_tr_volume_cb_idx = mpt3sas_base_register_callback_handler(
	    _scsih_tm_volume_tr_complete);

	tm_sas_control_cb_idx = mpt3sas_base_register_callback_handler(
	    _scsih_sas_control_complete);

	return 0;
}
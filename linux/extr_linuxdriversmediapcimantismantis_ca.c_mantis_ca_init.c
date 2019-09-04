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
struct dvb_adapter {int dummy; } ;
struct mantis_pci {struct mantis_ca* mantis_ca; struct dvb_adapter dvb_adapter; } ;
struct TYPE_2__ {struct mantis_ca* data; int /*<<< orphan*/  poll_slot_status; int /*<<< orphan*/  slot_ts_enable; int /*<<< orphan*/  slot_shutdown; int /*<<< orphan*/  slot_reset; int /*<<< orphan*/  write_cam_control; int /*<<< orphan*/  read_cam_control; int /*<<< orphan*/  write_attribute_mem; int /*<<< orphan*/  read_attribute_mem; int /*<<< orphan*/  owner; } ;
struct mantis_ca {TYPE_1__ en50221; int /*<<< orphan*/  hif_write_wq; int /*<<< orphan*/  hif_opdone_wq; int /*<<< orphan*/  hif_data_wq; int /*<<< orphan*/  ca_lock; struct mantis_pci* ca_priv; } ;

/* Variables and functions */
 int DVB_CA_EN50221_FLAG_IRQ_CAMCHANGE ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  MANTIS_DEBUG ; 
 int /*<<< orphan*/  MANTIS_ERROR ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int /*<<< orphan*/  dprintk (int /*<<< orphan*/ ,int,char*,...) ; 
 int dvb_ca_en50221_init (struct dvb_adapter*,TYPE_1__*,int,int) ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct mantis_ca*) ; 
 struct mantis_ca* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mantis_ca_read_attr_mem ; 
 int /*<<< orphan*/  mantis_ca_read_cam_ctl ; 
 int /*<<< orphan*/  mantis_ca_slot_reset ; 
 int /*<<< orphan*/  mantis_ca_slot_shutdown ; 
 int /*<<< orphan*/  mantis_ca_write_attr_mem ; 
 int /*<<< orphan*/  mantis_ca_write_cam_ctl ; 
 int /*<<< orphan*/  mantis_evmgr_init (struct mantis_ca*) ; 
 int /*<<< orphan*/  mantis_slot_status ; 
 int /*<<< orphan*/  mantis_ts_control ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 

int mantis_ca_init(struct mantis_pci *mantis)
{
	struct dvb_adapter *dvb_adapter	= &mantis->dvb_adapter;
	struct mantis_ca *ca;
	int ca_flags = 0, result;

	dprintk(MANTIS_DEBUG, 1, "Initializing Mantis CA");
	ca = kzalloc(sizeof(struct mantis_ca), GFP_KERNEL);
	if (!ca) {
		dprintk(MANTIS_ERROR, 1, "Out of memory!, exiting ..");
		result = -ENOMEM;
		goto err;
	}

	ca->ca_priv		= mantis;
	mantis->mantis_ca	= ca;
	ca_flags		= DVB_CA_EN50221_FLAG_IRQ_CAMCHANGE;
	/* register CA interface */
	ca->en50221.owner		= THIS_MODULE;
	ca->en50221.read_attribute_mem	= mantis_ca_read_attr_mem;
	ca->en50221.write_attribute_mem	= mantis_ca_write_attr_mem;
	ca->en50221.read_cam_control	= mantis_ca_read_cam_ctl;
	ca->en50221.write_cam_control	= mantis_ca_write_cam_ctl;
	ca->en50221.slot_reset		= mantis_ca_slot_reset;
	ca->en50221.slot_shutdown	= mantis_ca_slot_shutdown;
	ca->en50221.slot_ts_enable	= mantis_ts_control;
	ca->en50221.poll_slot_status	= mantis_slot_status;
	ca->en50221.data		= ca;

	mutex_init(&ca->ca_lock);

	init_waitqueue_head(&ca->hif_data_wq);
	init_waitqueue_head(&ca->hif_opdone_wq);
	init_waitqueue_head(&ca->hif_write_wq);

	dprintk(MANTIS_ERROR, 1, "Registering EN50221 device");
	result = dvb_ca_en50221_init(dvb_adapter, &ca->en50221, ca_flags, 1);
	if (result != 0) {
		dprintk(MANTIS_ERROR, 1, "EN50221: Initialization failed <%d>", result);
		goto err;
	}
	dprintk(MANTIS_ERROR, 1, "Registered EN50221 device");
	mantis_evmgr_init(ca);
	return 0;
err:
	kfree(ca);
	return result;
}
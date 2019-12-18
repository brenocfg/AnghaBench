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
struct scsi_device {struct clariion_dh_data* handler_data; } ;
struct clariion_dh_data {size_t lun_state; void* default_sp; int /*<<< orphan*/  port; void* current_sp; } ;

/* Variables and functions */
 size_t CLARIION_LUN_UNINITIALIZED ; 
 int /*<<< orphan*/  CLARIION_NAME ; 
 void* CLARIION_UNBOUND_LU ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  KERN_INFO ; 
 int SCSI_DH_NOMEM ; 
 int SCSI_DH_OK ; 
 int clariion_send_inquiry (struct scsi_device*,struct clariion_dh_data*) ; 
 int clariion_std_inquiry (struct scsi_device*,struct clariion_dh_data*) ; 
 int /*<<< orphan*/  kfree (struct clariion_dh_data*) ; 
 struct clariion_dh_data* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * lun_state ; 
 int /*<<< orphan*/  sdev_printk (int /*<<< orphan*/ ,struct scsi_device*,char*,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*) ; 

__attribute__((used)) static int clariion_bus_attach(struct scsi_device *sdev)
{
	struct clariion_dh_data *h;
	int err;

	h = kzalloc(sizeof(*h) , GFP_KERNEL);
	if (!h)
		return SCSI_DH_NOMEM;
	h->lun_state = CLARIION_LUN_UNINITIALIZED;
	h->default_sp = CLARIION_UNBOUND_LU;
	h->current_sp = CLARIION_UNBOUND_LU;

	err = clariion_std_inquiry(sdev, h);
	if (err != SCSI_DH_OK)
		goto failed;

	err = clariion_send_inquiry(sdev, h);
	if (err != SCSI_DH_OK)
		goto failed;

	sdev_printk(KERN_INFO, sdev,
		    "%s: connected to SP %c Port %d (%s, default SP %c)\n",
		    CLARIION_NAME, h->current_sp + 'A',
		    h->port, lun_state[h->lun_state],
		    h->default_sp + 'A');

	sdev->handler_data = h;
	return SCSI_DH_OK;

failed:
	kfree(h);
	return err;
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct scsi_device {int dummy; } ;
struct c4_inquiry {int* slot_id; } ;
struct TYPE_3__ {struct c4_inquiry c4; } ;
struct rdac_dh_data {struct scsi_device* sdev; TYPE_2__* ctlr; int /*<<< orphan*/  node; TYPE_1__ inq; } ;
struct TYPE_4__ {int /*<<< orphan*/  dh_list; } ;

/* Variables and functions */
 int SCSI_DH_IO ; 
 int SCSI_DH_OK ; 
 int SCSI_DH_RES_TEMP_UNAVAIL ; 
 TYPE_2__* get_controller (int,char*,int /*<<< orphan*/ *,struct scsi_device*) ; 
 int /*<<< orphan*/  list_add_rcu (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_lock ; 
 int /*<<< orphan*/  scsi_get_vpd_page (struct scsi_device*,int,unsigned char*,int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int initialize_controller(struct scsi_device *sdev,
		struct rdac_dh_data *h, char *array_name, u8 *array_id)
{
	int err = SCSI_DH_IO, index;
	struct c4_inquiry *inqp = &h->inq.c4;

	if (!scsi_get_vpd_page(sdev, 0xC4, (unsigned char *)inqp,
			       sizeof(struct c4_inquiry))) {
		/* get the controller index */
		if (inqp->slot_id[1] == 0x31)
			index = 0;
		else
			index = 1;

		spin_lock(&list_lock);
		h->ctlr = get_controller(index, array_name, array_id, sdev);
		if (!h->ctlr)
			err = SCSI_DH_RES_TEMP_UNAVAIL;
		else {
			list_add_rcu(&h->node, &h->ctlr->dh_list);
			h->sdev = sdev;
		}
		spin_unlock(&list_lock);
		err = SCSI_DH_OK;
	}
	return err;
}
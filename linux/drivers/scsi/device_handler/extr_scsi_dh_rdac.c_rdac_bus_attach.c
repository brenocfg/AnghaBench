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
struct scsi_device {struct rdac_dh_data* handler_data; } ;
struct rdac_dh_data {TYPE_1__* ctlr; scalar_t__ lun_state; scalar_t__ mode; int /*<<< orphan*/  lun; int /*<<< orphan*/  state; } ;
struct TYPE_2__ {int /*<<< orphan*/  kref; } ;

/* Variables and functions */
 int ARRAY_LABEL_LEN ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  KERN_NOTICE ; 
 int /*<<< orphan*/  RDAC_NAME ; 
 int /*<<< orphan*/  RDAC_STATE_ACTIVE ; 
 int SCSI_DH_NOMEM ; 
 int SCSI_DH_OK ; 
 int /*<<< orphan*/  UNINITIALIZED_LUN ; 
 int UNIQUE_ID_LEN ; 
 int check_ownership (struct scsi_device*,struct rdac_dh_data*) ; 
 int get_lun_info (struct scsi_device*,struct rdac_dh_data*,char*,char*) ; 
 int initialize_controller (struct scsi_device*,struct rdac_dh_data*,char*,char*) ; 
 int /*<<< orphan*/  kfree (struct rdac_dh_data*) ; 
 int /*<<< orphan*/  kref_put (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct rdac_dh_data* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_lock ; 
 int /*<<< orphan*/ * lun_state ; 
 int /*<<< orphan*/ * mode ; 
 int /*<<< orphan*/  release_controller ; 
 int /*<<< orphan*/  sdev_printk (int /*<<< orphan*/ ,struct scsi_device*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int set_mode_select (struct scsi_device*,struct rdac_dh_data*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int rdac_bus_attach(struct scsi_device *sdev)
{
	struct rdac_dh_data *h;
	int err;
	char array_name[ARRAY_LABEL_LEN];
	char array_id[UNIQUE_ID_LEN];

	h = kzalloc(sizeof(*h) , GFP_KERNEL);
	if (!h)
		return SCSI_DH_NOMEM;
	h->lun = UNINITIALIZED_LUN;
	h->state = RDAC_STATE_ACTIVE;

	err = get_lun_info(sdev, h, array_name, array_id);
	if (err != SCSI_DH_OK)
		goto failed;

	err = initialize_controller(sdev, h, array_name, array_id);
	if (err != SCSI_DH_OK)
		goto failed;

	err = check_ownership(sdev, h);
	if (err != SCSI_DH_OK)
		goto clean_ctlr;

	err = set_mode_select(sdev, h);
	if (err != SCSI_DH_OK)
		goto clean_ctlr;

	sdev_printk(KERN_NOTICE, sdev,
		    "%s: LUN %d (%s) (%s)\n",
		    RDAC_NAME, h->lun, mode[(int)h->mode],
		    lun_state[(int)h->lun_state]);

	sdev->handler_data = h;
	return SCSI_DH_OK;

clean_ctlr:
	spin_lock(&list_lock);
	kref_put(&h->ctlr->kref, release_controller);
	spin_unlock(&list_lock);

failed:
	kfree(h);
	return err;
}
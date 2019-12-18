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
struct scsi_device {struct alua_dh_data* handler_data; } ;
struct alua_queue_data {void* callback_data; int /*<<< orphan*/  (* callback_fn ) (void*,int) ;} ;
struct alua_port_group {int /*<<< orphan*/  kref; } ;
struct alua_dh_data {int init_error; int /*<<< orphan*/  init_mutex; int /*<<< orphan*/  pg; } ;
typedef  int /*<<< orphan*/  (* activate_complete ) (void*,int) ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int SCSI_DH_DEV_OFFLINED ; 
 int SCSI_DH_OK ; 
 int SCSI_DH_RES_TEMP_UNAVAIL ; 
 scalar_t__ alua_rtpg_queue (struct alua_port_group*,struct scsi_device*,struct alua_queue_data*,int) ; 
 int /*<<< orphan*/  kfree (struct alua_queue_data*) ; 
 int /*<<< orphan*/  kref_get_unless_zero (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kref_put (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct alua_queue_data* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct alua_port_group* rcu_dereference (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int /*<<< orphan*/  release_port_group ; 

__attribute__((used)) static int alua_activate(struct scsi_device *sdev,
			activate_complete fn, void *data)
{
	struct alua_dh_data *h = sdev->handler_data;
	int err = SCSI_DH_OK;
	struct alua_queue_data *qdata;
	struct alua_port_group *pg;

	qdata = kzalloc(sizeof(*qdata), GFP_KERNEL);
	if (!qdata) {
		err = SCSI_DH_RES_TEMP_UNAVAIL;
		goto out;
	}
	qdata->callback_fn = fn;
	qdata->callback_data = data;

	mutex_lock(&h->init_mutex);
	rcu_read_lock();
	pg = rcu_dereference(h->pg);
	if (!pg || !kref_get_unless_zero(&pg->kref)) {
		rcu_read_unlock();
		kfree(qdata);
		err = h->init_error;
		mutex_unlock(&h->init_mutex);
		goto out;
	}
	rcu_read_unlock();
	mutex_unlock(&h->init_mutex);

	if (alua_rtpg_queue(pg, sdev, qdata, true))
		fn = NULL;
	else
		err = SCSI_DH_DEV_OFFLINED;
	kref_put(&pg->kref, release_port_group);
out:
	if (fn)
		fn(data, err);
	return 0;
}
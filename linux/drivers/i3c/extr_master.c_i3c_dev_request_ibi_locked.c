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
struct i3c_master_controller {TYPE_1__* ops; } ;
struct i3c_ibi_setup {int /*<<< orphan*/  num_slots; int /*<<< orphan*/  max_payload_len; int /*<<< orphan*/  handler; } ;
struct i3c_device_ibi_info {int /*<<< orphan*/  num_slots; int /*<<< orphan*/  max_payload_len; int /*<<< orphan*/  handler; int /*<<< orphan*/  all_ibis_handled; int /*<<< orphan*/  pending_ibis; } ;
struct i3c_dev_desc {struct i3c_device_ibi_info* ibi; } ;
struct TYPE_2__ {int (* request_ibi ) (struct i3c_dev_desc*,struct i3c_ibi_setup const*) ;} ;

/* Variables and functions */
 int EBUSY ; 
 int ENOMEM ; 
 int ENOTSUPP ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct i3c_master_controller* i3c_dev_get_master (struct i3c_dev_desc*) ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct i3c_device_ibi_info*) ; 
 struct i3c_device_ibi_info* kzalloc (int,int /*<<< orphan*/ ) ; 
 int stub1 (struct i3c_dev_desc*,struct i3c_ibi_setup const*) ; 

int i3c_dev_request_ibi_locked(struct i3c_dev_desc *dev,
			       const struct i3c_ibi_setup *req)
{
	struct i3c_master_controller *master = i3c_dev_get_master(dev);
	struct i3c_device_ibi_info *ibi;
	int ret;

	if (!master->ops->request_ibi)
		return -ENOTSUPP;

	if (dev->ibi)
		return -EBUSY;

	ibi = kzalloc(sizeof(*ibi), GFP_KERNEL);
	if (!ibi)
		return -ENOMEM;

	atomic_set(&ibi->pending_ibis, 0);
	init_completion(&ibi->all_ibis_handled);
	ibi->handler = req->handler;
	ibi->max_payload_len = req->max_payload_len;
	ibi->num_slots = req->num_slots;

	dev->ibi = ibi;
	ret = master->ops->request_ibi(dev, req);
	if (ret) {
		kfree(ibi);
		dev->ibi = NULL;
	}

	return ret;
}
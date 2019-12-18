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
typedef  void* u8 ;
struct hidpp_ff_work_data {int effect_id; int /*<<< orphan*/  work; int /*<<< orphan*/  params; void* size; void* command; struct hidpp_ff_private_data* data; } ;
struct hidpp_ff_private_data {TYPE_1__* hidpp; int /*<<< orphan*/  workqueue_size; int /*<<< orphan*/  wq; } ;
struct TYPE_2__ {int /*<<< orphan*/  hid_dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hid_warn (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  hidpp_ff_work_handler ; 
 struct hidpp_ff_work_data* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,void**,void*) ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int hidpp_ff_queue_work(struct hidpp_ff_private_data *data, int effect_id, u8 command, u8 *params, u8 size)
{
	struct hidpp_ff_work_data *wd = kzalloc(sizeof(*wd), GFP_KERNEL);
	int s;

	if (!wd)
		return -ENOMEM;

	INIT_WORK(&wd->work, hidpp_ff_work_handler);

	wd->data = data;
	wd->effect_id = effect_id;
	wd->command = command;
	wd->size = size;
	memcpy(wd->params, params, size);

	atomic_inc(&data->workqueue_size);
	queue_work(data->wq, &wd->work);

	/* warn about excessive queue size */
	s = atomic_read(&data->workqueue_size);
	if (s >= 20 && s % 20 == 0)
		hid_warn(data->hidpp->hid_dev, "Force feedback command queue contains %d commands, causing substantial delays!", s);

	return 0;
}
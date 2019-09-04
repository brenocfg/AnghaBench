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
struct seq_file {struct drbd_device* private; } ;
struct drbd_md {int /*<<< orphan*/  uuid_lock; int /*<<< orphan*/ * uuid; } ;
struct drbd_device {TYPE_1__* ldev; } ;
typedef  enum drbd_uuid_index { ____Placeholder_drbd_uuid_index } drbd_uuid_index ;
struct TYPE_2__ {struct drbd_md md; } ;

/* Variables and functions */
 int /*<<< orphan*/  D_FAILED ; 
 int ENODEV ; 
 int UI_CURRENT ; 
 int UI_HISTORY_END ; 
 int /*<<< orphan*/  get_ldev_if_state (struct drbd_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  put_ldev (struct drbd_device*) ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int device_data_gen_id_show(struct seq_file *m, void *ignored)
{
	struct drbd_device *device = m->private;
	struct drbd_md *md;
	enum drbd_uuid_index idx;

	if (!get_ldev_if_state(device, D_FAILED))
		return -ENODEV;

	md = &device->ldev->md;
	spin_lock_irq(&md->uuid_lock);
	for (idx = UI_CURRENT; idx <= UI_HISTORY_END; idx++) {
		seq_printf(m, "0x%016llX\n", md->uuid[idx]);
	}
	spin_unlock_irq(&md->uuid_lock);
	put_ldev(device);
	return 0;
}
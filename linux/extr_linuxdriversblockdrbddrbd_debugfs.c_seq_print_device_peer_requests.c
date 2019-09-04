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
struct seq_file {int dummy; } ;
struct drbd_device {scalar_t__ flush_jif; int /*<<< orphan*/  vnr; int /*<<< orphan*/  minor; int /*<<< orphan*/  flags; TYPE_1__* resource; int /*<<< orphan*/  sync_ee; int /*<<< orphan*/  read_ee; int /*<<< orphan*/  active_ee; } ;
struct TYPE_2__ {int /*<<< orphan*/  req_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  FLUSH_PENDING ; 
 int /*<<< orphan*/  jiffies_to_msecs (scalar_t__) ; 
 int /*<<< orphan*/  seq_print_peer_request (struct seq_file*,struct drbd_device*,int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  seq_puts (struct seq_file*,char*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void seq_print_device_peer_requests(struct seq_file *m,
	struct drbd_device *device, unsigned long now)
{
	seq_puts(m, "minor\tvnr\tsector\tsize\trw\tage\tflags\n");
	spin_lock_irq(&device->resource->req_lock);
	seq_print_peer_request(m, device, &device->active_ee, now);
	seq_print_peer_request(m, device, &device->read_ee, now);
	seq_print_peer_request(m, device, &device->sync_ee, now);
	spin_unlock_irq(&device->resource->req_lock);
	if (test_bit(FLUSH_PENDING, &device->flags)) {
		seq_printf(m, "%u\t%u\t-\t-\tF\t%u\tflush\n",
			device->minor, device->vnr,
			jiffies_to_msecs(now - device->flush_jif));
	}
}
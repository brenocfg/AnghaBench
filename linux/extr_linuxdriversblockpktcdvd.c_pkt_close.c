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
struct pktcdvd_device {scalar_t__ refcnt; int /*<<< orphan*/  flags; } ;
struct gendisk {struct pktcdvd_device* private_data; } ;
typedef  int /*<<< orphan*/  fmode_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  PACKET_WRITABLE ; 
 int /*<<< orphan*/  ctl_mutex ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pkt_release_dev (struct pktcdvd_device*,int) ; 
 int /*<<< orphan*/  pktcdvd_mutex ; 
 int test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void pkt_close(struct gendisk *disk, fmode_t mode)
{
	struct pktcdvd_device *pd = disk->private_data;

	mutex_lock(&pktcdvd_mutex);
	mutex_lock(&ctl_mutex);
	pd->refcnt--;
	BUG_ON(pd->refcnt < 0);
	if (pd->refcnt == 0) {
		int flush = test_bit(PACKET_WRITABLE, &pd->flags);
		pkt_release_dev(pd, flush);
	}
	mutex_unlock(&ctl_mutex);
	mutex_unlock(&pktcdvd_mutex);
}
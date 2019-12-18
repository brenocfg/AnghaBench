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
struct dm_delay_info {unsigned long expires; int /*<<< orphan*/  list; struct delay_c* context; } ;
struct delay_class {int /*<<< orphan*/  ops; int /*<<< orphan*/  delay; } ;
struct delay_c {int /*<<< orphan*/  delayed_bios; int /*<<< orphan*/  may_delay; } ;
struct bio {int dummy; } ;

/* Variables and functions */
 int DM_MAPIO_REMAPPED ; 
 int DM_MAPIO_SUBMITTED ; 
 int /*<<< orphan*/  atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  delayed_bios_lock ; 
 struct dm_delay_info* dm_per_bio_data (struct bio*,int) ; 
 unsigned long jiffies ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 unsigned long msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  queue_timeout (struct delay_c*,unsigned long) ; 

__attribute__((used)) static int delay_bio(struct delay_c *dc, struct delay_class *c, struct bio *bio)
{
	struct dm_delay_info *delayed;
	unsigned long expires = 0;

	if (!c->delay || !atomic_read(&dc->may_delay))
		return DM_MAPIO_REMAPPED;

	delayed = dm_per_bio_data(bio, sizeof(struct dm_delay_info));

	delayed->context = dc;
	delayed->expires = expires = jiffies + msecs_to_jiffies(c->delay);

	mutex_lock(&delayed_bios_lock);
	c->ops++;
	list_add_tail(&delayed->list, &dc->delayed_bios);
	mutex_unlock(&delayed_bios_lock);

	queue_timeout(dc, expires);

	return DM_MAPIO_SUBMITTED;
}
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
struct map_info {scalar_t__ virt; scalar_t__ map_priv_1; } ;
struct latch_addr_flash_info {int win_mask; int /*<<< orphan*/  lock; int /*<<< orphan*/  data; int /*<<< orphan*/  (* set_window ) (unsigned long,int /*<<< orphan*/ ) ;} ;
typedef  unsigned int ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy_fromio (void*,scalar_t__,unsigned int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (unsigned long,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void lf_copy_from(struct map_info *map, void *to,
		unsigned long from, ssize_t len)
{
	struct latch_addr_flash_info *info =
		(struct latch_addr_flash_info *) map->map_priv_1;
	unsigned n;

	while (len > 0) {
		n = info->win_mask + 1 - (from & info->win_mask);
		if (n > len)
			n = len;

		spin_lock(&info->lock);

		info->set_window(from, info->data);
		memcpy_fromio(to, map->virt + (from & info->win_mask), n);

		spin_unlock(&info->lock);

		to += n;
		from += n;
		len -= n;
	}
}
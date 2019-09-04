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
struct ubi_ltree_entry {scalar_t__ users; int /*<<< orphan*/  rb; int /*<<< orphan*/  mutex; } ;
struct ubi_device {int /*<<< orphan*/  ltree_lock; int /*<<< orphan*/  ltree; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct ubi_ltree_entry*) ; 
 struct ubi_ltree_entry* ltree_lookup (struct ubi_device*,int,int) ; 
 int /*<<< orphan*/  rb_erase (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ubi_assert (int) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void leb_write_unlock(struct ubi_device *ubi, int vol_id, int lnum)
{
	struct ubi_ltree_entry *le;

	spin_lock(&ubi->ltree_lock);
	le = ltree_lookup(ubi, vol_id, lnum);
	le->users -= 1;
	ubi_assert(le->users >= 0);
	up_write(&le->mutex);
	if (le->users == 0) {
		rb_erase(&le->rb, &ubi->ltree);
		kfree(le);
	}
	spin_unlock(&ubi->ltree_lock);
}
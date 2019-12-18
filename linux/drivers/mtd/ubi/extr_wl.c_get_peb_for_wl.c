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
struct TYPE_2__ {int /*<<< orphan*/  rb; } ;
struct ubi_wl_entry {TYPE_1__ u; } ;
struct ubi_device {scalar_t__ free_count; int /*<<< orphan*/  free; } ;

/* Variables and functions */
 int /*<<< orphan*/  WL_FREE_MAX_DIFF ; 
 struct ubi_wl_entry* find_wl_entry (struct ubi_device*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rb_erase (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  self_check_in_wl_tree (struct ubi_device*,struct ubi_wl_entry*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ubi_assert (int) ; 

__attribute__((used)) static struct ubi_wl_entry *get_peb_for_wl(struct ubi_device *ubi)
{
	struct ubi_wl_entry *e;

	e = find_wl_entry(ubi, &ubi->free, WL_FREE_MAX_DIFF);
	self_check_in_wl_tree(ubi, e, &ubi->free);
	ubi->free_count--;
	ubi_assert(ubi->free_count >= 0);
	rb_erase(&e->u.rb, &ubi->free);

	return e;
}
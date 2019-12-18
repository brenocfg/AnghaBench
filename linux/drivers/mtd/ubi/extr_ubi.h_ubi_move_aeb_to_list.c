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
struct ubi_ainf_volume {int /*<<< orphan*/  root; } ;
struct TYPE_2__ {int /*<<< orphan*/  list; int /*<<< orphan*/  rb; } ;
struct ubi_ainf_peb {TYPE_1__ u; } ;
struct list_head {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,struct list_head*) ; 
 int /*<<< orphan*/  rb_erase (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void ubi_move_aeb_to_list(struct ubi_ainf_volume *av,
					 struct ubi_ainf_peb *aeb,
					 struct list_head *list)
{
		rb_erase(&aeb->u.rb, &av->root);
		list_add_tail(&aeb->u.list, list);
}
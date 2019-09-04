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
struct vmw_mob {int /*<<< orphan*/  num_pages; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct vmw_mob* kzalloc (int,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  vmw_mob_calculate_pt_pages (unsigned long) ; 

struct vmw_mob *vmw_mob_create(unsigned long data_pages)
{
	struct vmw_mob *mob = kzalloc(sizeof(*mob), GFP_KERNEL);

	if (unlikely(!mob))
		return NULL;

	mob->num_pages = vmw_mob_calculate_pt_pages(data_pages);

	return mob;
}
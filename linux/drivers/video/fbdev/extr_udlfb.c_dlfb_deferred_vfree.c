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
struct dlfb_deferred_free {int /*<<< orphan*/  list; void* mem; } ;
struct dlfb_data {int /*<<< orphan*/  deferred_free; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct dlfb_deferred_free* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void dlfb_deferred_vfree(struct dlfb_data *dlfb, void *mem)
{
	struct dlfb_deferred_free *d = kmalloc(sizeof(struct dlfb_deferred_free), GFP_KERNEL);
	if (!d)
		return;
	d->mem = mem;
	list_add(&d->list, &dlfb->deferred_free);
}
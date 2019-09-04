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
struct xen_gem_object {int /*<<< orphan*/ * pages; } ;

/* Variables and functions */
 int /*<<< orphan*/  kvfree (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void gem_free_pages_array(struct xen_gem_object *xen_obj)
{
	kvfree(xen_obj->pages);
	xen_obj->pages = NULL;
}
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
struct ubi_wl_entry {size_t pnum; } ;
struct ubi_device {int /*<<< orphan*/ ** lookuptbl; } ;

/* Variables and functions */
 int /*<<< orphan*/  kmem_cache_free (int /*<<< orphan*/ ,struct ubi_wl_entry*) ; 
 int /*<<< orphan*/  ubi_wl_entry_slab ; 

__attribute__((used)) static void wl_entry_destroy(struct ubi_device *ubi, struct ubi_wl_entry *e)
{
	ubi->lookuptbl[e->pnum] = NULL;
	kmem_cache_free(ubi_wl_entry_slab, e);
}
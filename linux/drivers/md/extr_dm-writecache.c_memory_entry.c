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
struct wc_memory_entry {int dummy; } ;
struct wc_entry {size_t index; } ;
struct dm_writecache {int dummy; } ;
struct TYPE_2__ {struct wc_memory_entry* entries; } ;

/* Variables and functions */
 TYPE_1__* sb (struct dm_writecache*) ; 

__attribute__((used)) static struct wc_memory_entry *memory_entry(struct dm_writecache *wc, struct wc_entry *e)
{
	return &sb(wc)->entries[e->index];
}
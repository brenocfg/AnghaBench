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
typedef  int u8 ;
struct rsm_map_table {scalar_t__ used; int /*<<< orphan*/  map; } ;
struct hfi1_devdata {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ is_ax (struct hfi1_devdata*) ; 
 struct rsm_map_table* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static struct rsm_map_table *alloc_rsm_map_table(struct hfi1_devdata *dd)
{
	struct rsm_map_table *rmt;
	u8 rxcontext = is_ax(dd) ? 0 : 0xff;  /* 0 is default if a0 ver. */

	rmt = kmalloc(sizeof(*rmt), GFP_KERNEL);
	if (rmt) {
		memset(rmt->map, rxcontext, sizeof(rmt->map));
		rmt->used = 0;
	}

	return rmt;
}
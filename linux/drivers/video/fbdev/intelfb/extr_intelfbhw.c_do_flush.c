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
struct intelfb_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADVANCE_RING () ; 
 int MI_FLUSH ; 
 int MI_INVALIDATE_MAP_CACHE ; 
 int MI_NOOP ; 
 int MI_WRITE_DIRTY_STATE ; 
 int /*<<< orphan*/  OUT_RING (int) ; 
 int /*<<< orphan*/  START_RING (int) ; 

__attribute__((used)) static void do_flush(struct intelfb_info *dinfo)
{
	START_RING(2);
	OUT_RING(MI_FLUSH | MI_WRITE_DIRTY_STATE | MI_INVALIDATE_MAP_CACHE);
	OUT_RING(MI_NOOP);
	ADVANCE_RING();
}
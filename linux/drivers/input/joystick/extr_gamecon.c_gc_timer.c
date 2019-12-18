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
struct timer_list {int dummy; } ;
struct gc {int /*<<< orphan*/  timer; scalar_t__* pad_count; } ;

/* Variables and functions */
 size_t GC_DDR ; 
 size_t GC_MULTI ; 
 size_t GC_MULTI2 ; 
 size_t GC_N64 ; 
 size_t GC_NES ; 
 size_t GC_PSX ; 
 scalar_t__ GC_REFRESH_TIME ; 
 size_t GC_SNES ; 
 size_t GC_SNESMOUSE ; 
 struct gc* from_timer (int /*<<< orphan*/ ,struct timer_list*,int /*<<< orphan*/ ) ; 
 struct gc* gc ; 
 int /*<<< orphan*/  gc_multi_process_packet (struct gc*) ; 
 int /*<<< orphan*/  gc_n64_process_packet (struct gc*) ; 
 int /*<<< orphan*/  gc_nes_process_packet (struct gc*) ; 
 int /*<<< orphan*/  gc_psx_process_packet (struct gc*) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  timer ; 

__attribute__((used)) static void gc_timer(struct timer_list *t)
{
	struct gc *gc = from_timer(gc, t, timer);

/*
 * N64 pads - must be read first, any read confuses them for 200 us
 */

	if (gc->pad_count[GC_N64])
		gc_n64_process_packet(gc);

/*
 * NES and SNES pads or mouse
 */

	if (gc->pad_count[GC_NES] ||
	    gc->pad_count[GC_SNES] ||
	    gc->pad_count[GC_SNESMOUSE]) {
		gc_nes_process_packet(gc);
	}

/*
 * Multi and Multi2 joysticks
 */

	if (gc->pad_count[GC_MULTI] || gc->pad_count[GC_MULTI2])
		gc_multi_process_packet(gc);

/*
 * PSX controllers
 */

	if (gc->pad_count[GC_PSX] || gc->pad_count[GC_DDR])
		gc_psx_process_packet(gc);

	mod_timer(&gc->timer, jiffies + GC_REFRESH_TIME);
}
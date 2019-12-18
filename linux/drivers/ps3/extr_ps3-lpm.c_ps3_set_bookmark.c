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
typedef  int /*<<< orphan*/  u64 ;

/* Variables and functions */
 int /*<<< orphan*/  SPRN_BKMK ; 
 int /*<<< orphan*/  mtspr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void ps3_set_bookmark(u64 bookmark)
{
	/*
	 * As per the PPE book IV, to avoid bookmark loss there must
	 * not be a traced branch within 10 cycles of setting the
	 * SPRN_BKMK register.  The actual text is unclear if 'within'
	 * includes cycles before the call.
	 */

	asm volatile("nop;nop;nop;nop;nop;nop;nop;nop;nop;");
	mtspr(SPRN_BKMK, bookmark);
	asm volatile("nop;nop;nop;nop;nop;nop;nop;nop;nop;");
}
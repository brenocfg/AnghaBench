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
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_2__ {int /*<<< orphan*/  mute; } ;
struct fmr2 {int /*<<< orphan*/  io; TYPE_1__ tea; } ;

/* Variables and functions */
 int /*<<< orphan*/  STR_WREN ; 
 int /*<<< orphan*/  outb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void tc9154a_set_pins(struct fmr2 *fmr2, u8 pins)
{
	if (!fmr2->tea.mute)
		pins |= STR_WREN;

	outb(pins, fmr2->io);
}
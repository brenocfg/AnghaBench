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
struct etmv4_config {int eventctrl0; int eventctrl1; int stall_ctrl; int syncfreq; int ts_ctrl; int /*<<< orphan*/  vinst_ctrl; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void etm4_set_default_config(struct etmv4_config *config)
{
	/* disable all events tracing */
	config->eventctrl0 = 0x0;
	config->eventctrl1 = 0x0;

	/* disable stalling */
	config->stall_ctrl = 0x0;

	/* enable trace synchronization every 4096 bytes, if available */
	config->syncfreq = 0xC;

	/* disable timestamp event */
	config->ts_ctrl = 0x0;

	/* TRCVICTLR::EVENT = 0x01, select the always on logic */
	config->vinst_ctrl |= BIT(0);
}
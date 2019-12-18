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
struct topstar_laptop {int /*<<< orphan*/  input; } ;

/* Variables and functions */
 int /*<<< orphan*/  pr_info (char*,int) ; 
 int /*<<< orphan*/  sparse_keymap_report_event (int /*<<< orphan*/ ,int,int,int) ; 

__attribute__((used)) static void topstar_input_notify(struct topstar_laptop *topstar, int event)
{
	if (!sparse_keymap_report_event(topstar->input, event, 1, true))
		pr_info("unknown event = 0x%02x\n", event);
}
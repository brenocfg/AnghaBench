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
struct cs5535_mfgpt_timer {int nr; } ;

/* Variables and functions */
 int /*<<< orphan*/  MFGPT_CMP1 ; 
 int /*<<< orphan*/  MFGPT_CMP2 ; 
 int /*<<< orphan*/  MFGPT_EVENT_IRQ ; 
 int /*<<< orphan*/  MFGPT_EVENT_NMI ; 
 int /*<<< orphan*/  MFGPT_EVENT_RESET ; 
 int MFGPT_MAX_TIMERS ; 
 int /*<<< orphan*/  cs5535_mfgpt_toggle_event (struct cs5535_mfgpt_timer*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void soft_reset(void)
{
	int i;
	struct cs5535_mfgpt_timer t;

	for (i = 0; i < MFGPT_MAX_TIMERS; i++) {
		t.nr = i;

		cs5535_mfgpt_toggle_event(&t, MFGPT_CMP1, MFGPT_EVENT_RESET, 0);
		cs5535_mfgpt_toggle_event(&t, MFGPT_CMP2, MFGPT_EVENT_RESET, 0);
		cs5535_mfgpt_toggle_event(&t, MFGPT_CMP1, MFGPT_EVENT_NMI, 0);
		cs5535_mfgpt_toggle_event(&t, MFGPT_CMP2, MFGPT_EVENT_NMI, 0);
		cs5535_mfgpt_toggle_event(&t, MFGPT_CMP1, MFGPT_EVENT_IRQ, 0);
		cs5535_mfgpt_toggle_event(&t, MFGPT_CMP2, MFGPT_EVENT_IRQ, 0);
	}
}
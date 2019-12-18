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
struct evtchn_unmask {unsigned int port; } ;
typedef  int /*<<< orphan*/  event_word_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  EVTCHNOP_unmask ; 
 int /*<<< orphan*/  HYPERVISOR_event_channel_op (int /*<<< orphan*/ ,struct evtchn_unmask*) ; 
 int /*<<< orphan*/  clear_masked (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * event_word_from_port (unsigned int) ; 
 scalar_t__ evtchn_fifo_is_pending (unsigned int) ; 
 int /*<<< orphan*/  irqs_disabled () ; 

__attribute__((used)) static void evtchn_fifo_unmask(unsigned port)
{
	event_word_t *word = event_word_from_port(port);

	BUG_ON(!irqs_disabled());

	clear_masked(word);
	if (evtchn_fifo_is_pending(port)) {
		struct evtchn_unmask unmask = { .port = port };
		(void)HYPERVISOR_event_channel_op(EVTCHNOP_unmask, &unmask);
	}
}
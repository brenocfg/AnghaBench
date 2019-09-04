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
struct fm10k_intfc {int dummy; } ;

/* Variables and functions */
 scalar_t__ fm10k_set_qos_queues (struct fm10k_intfc*) ; 
 int /*<<< orphan*/  fm10k_set_rss_queues (struct fm10k_intfc*) ; 

__attribute__((used)) static void fm10k_set_num_queues(struct fm10k_intfc *interface)
{
	/* Attempt to setup QoS and RSS first */
	if (fm10k_set_qos_queues(interface))
		return;

	/* If we don't have QoS, just fallback to only RSS. */
	fm10k_set_rss_queues(interface);
}
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
struct igc_adapter {int dummy; } ;

/* Variables and functions */
 unsigned int IGC_MAX_RX_QUEUES ; 

unsigned int igc_get_max_rss_queues(struct igc_adapter *adapter)
{
	unsigned int max_rss_queues;

	/* Determine the maximum number of RSS queues supported. */
	max_rss_queues = IGC_MAX_RX_QUEUES;

	return max_rss_queues;
}
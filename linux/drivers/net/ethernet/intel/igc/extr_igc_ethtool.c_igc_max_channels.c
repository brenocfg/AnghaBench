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
 unsigned int igc_get_max_rss_queues (struct igc_adapter*) ; 

__attribute__((used)) static unsigned int igc_max_channels(struct igc_adapter *adapter)
{
	return igc_get_max_rss_queues(adapter);
}
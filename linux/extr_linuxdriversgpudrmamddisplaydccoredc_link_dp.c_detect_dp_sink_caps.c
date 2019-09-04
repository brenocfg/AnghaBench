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
struct dc_link {int dummy; } ;

/* Variables and functions */
 int retrieve_link_cap (struct dc_link*) ; 

bool detect_dp_sink_caps(struct dc_link *link)
{
	return retrieve_link_cap(link);

	/* dc init_hw has power encoder using default
	 * signal for connector. For native DP, no
	 * need to power up encoder again. If not native
	 * DP, hw_init may need check signal or power up
	 * encoder here.
	 */
	/* TODO save sink caps in link->sink */
}
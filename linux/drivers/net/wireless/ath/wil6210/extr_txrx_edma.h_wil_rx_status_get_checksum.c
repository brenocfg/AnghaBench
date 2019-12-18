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
struct wil_net_stats {int /*<<< orphan*/  rx_csum_err; } ;

/* Variables and functions */
 int CHECKSUM_NONE ; 
 int CHECKSUM_UNNECESSARY ; 
 int wil_rx_status_get_l3_rx_status (void*) ; 
 int wil_rx_status_get_l4_rx_status (void*) ; 

__attribute__((used)) static inline int wil_rx_status_get_checksum(void *msg,
					     struct wil_net_stats *stats)
{
	int l3_rx_status = wil_rx_status_get_l3_rx_status(msg);
	int l4_rx_status = wil_rx_status_get_l4_rx_status(msg);

	if (l4_rx_status == 1)
		return CHECKSUM_UNNECESSARY;

	if (l4_rx_status == 0 && l3_rx_status == 1)
		return CHECKSUM_UNNECESSARY;

	if (l3_rx_status == 0 && l4_rx_status == 0)
		/* L2 packet */
		return CHECKSUM_NONE;

	/* If HW reports bad checksum, let IP stack re-check it
	 * For example, HW doesn't understand Microsoft IP stack that
	 * mis-calculates TCP checksum - if it should be 0x0,
	 * it writes 0xffff in violation of RFC 1624
	 */
	stats->rx_csum_err++;
	return CHECKSUM_NONE;
}
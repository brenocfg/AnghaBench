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
struct rtllib_rx_stats {int /*<<< orphan*/  bFirstMPDU; int /*<<< orphan*/  bIsAMPDU; } ;

/* Variables and functions */

void rtl92e_copy_mpdu_stats(struct rtllib_rx_stats *psrc_stats,
			    struct rtllib_rx_stats *ptarget_stats)
{
	ptarget_stats->bIsAMPDU = psrc_stats->bIsAMPDU;
	ptarget_stats->bFirstMPDU = psrc_stats->bFirstMPDU;
}
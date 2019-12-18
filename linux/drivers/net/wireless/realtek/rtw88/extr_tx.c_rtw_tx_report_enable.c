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
struct rtw_tx_report {int /*<<< orphan*/  sn; } ;
struct rtw_tx_pkt_info {int sn; int report; } ;
struct rtw_dev {struct rtw_tx_report tx_report; } ;

/* Variables and functions */
 int atomic_inc_return (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void rtw_tx_report_enable(struct rtw_dev *rtwdev,
				 struct rtw_tx_pkt_info *pkt_info)
{
	struct rtw_tx_report *tx_report = &rtwdev->tx_report;

	/* [11:8], reserved, fills with zero
	 * [7:2],  tx report sequence number
	 * [1:0],  firmware use, fills with zero
	 */
	pkt_info->sn = (atomic_inc_return(&tx_report->sn) << 2) & 0xfc;
	pkt_info->report = true;
}
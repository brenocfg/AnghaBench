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
struct rx_ts_record {int rx_indicate_seq; int rx_timeout_indicate_seq; int /*<<< orphan*/  rx_admitted_ba_record; int /*<<< orphan*/  ts_common_info; } ;

/* Variables and functions */
 int /*<<< orphan*/  ResetBaEntry (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ResetTsCommonInfo (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ResetRxTsEntry(struct rx_ts_record *pTS)
{
	ResetTsCommonInfo(&pTS->ts_common_info);
	pTS->rx_indicate_seq = 0xffff; // This indicate the rx_indicate_seq is not used now!!
	pTS->rx_timeout_indicate_seq = 0xffff; // This indicate the rx_timeout_indicate_seq is not used now!!
	ResetBaEntry(&pTS->rx_admitted_ba_record);	  // For BA Recipient
}
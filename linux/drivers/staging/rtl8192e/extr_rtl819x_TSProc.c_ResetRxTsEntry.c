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
struct rx_ts_record {int RxIndicateSeq; int RxTimeoutIndicateSeq; int /*<<< orphan*/  RxAdmittedBARecord; int /*<<< orphan*/  TsCommonInfo; } ;

/* Variables and functions */
 int /*<<< orphan*/  ResetBaEntry (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ResetTsCommonInfo (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ResetRxTsEntry(struct rx_ts_record *pTS)
{
	ResetTsCommonInfo(&pTS->TsCommonInfo);
	pTS->RxIndicateSeq = 0xffff;
	pTS->RxTimeoutIndicateSeq = 0xffff;
	ResetBaEntry(&pTS->RxAdmittedBARecord);
}
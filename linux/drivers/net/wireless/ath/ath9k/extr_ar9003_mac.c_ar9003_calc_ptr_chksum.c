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
typedef  int u16 ;
struct ar9003_txc {int info; int link; int data0; int ctl3; int data1; int ctl5; int data2; int ctl7; int data3; int ctl9; } ;

/* Variables and functions */
 int AR_TxPtrChkSum ; 

__attribute__((used)) static u16 ar9003_calc_ptr_chksum(struct ar9003_txc *ads)
{
	int checksum;

	checksum = ads->info + ads->link
		+ ads->data0 + ads->ctl3
		+ ads->data1 + ads->ctl5
		+ ads->data2 + ads->ctl7
		+ ads->data3 + ads->ctl9;

	return ((checksum & 0xffff) + (checksum >> 16)) & AR_TxPtrChkSum;
}
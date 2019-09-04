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
struct rtsx_pcr {int /*<<< orphan*/ * ops; } ;

/* Variables and functions */
 int /*<<< orphan*/  rtl8402_pcr_ops ; 
 int /*<<< orphan*/  rtl8411 ; 
 int /*<<< orphan*/  rtl8411_init_common_params (struct rtsx_pcr*) ; 
 int /*<<< orphan*/  set_pull_ctrl_tables (struct rtsx_pcr*,int /*<<< orphan*/ ) ; 

void rtl8402_init_params(struct rtsx_pcr *pcr)
{
	rtl8411_init_common_params(pcr);
	pcr->ops = &rtl8402_pcr_ops;
	set_pull_ctrl_tables(pcr, rtl8411);
}
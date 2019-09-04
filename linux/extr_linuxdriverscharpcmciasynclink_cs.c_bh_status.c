#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ cts_chkcount; scalar_t__ dcd_chkcount; scalar_t__ dsr_chkcount; scalar_t__ ri_chkcount; } ;
typedef  TYPE_1__ MGSLPC_INFO ;

/* Variables and functions */

__attribute__((used)) static void bh_status(MGSLPC_INFO *info)
{
	info->ri_chkcount = 0;
	info->dsr_chkcount = 0;
	info->dcd_chkcount = 0;
	info->cts_chkcount = 0;
}
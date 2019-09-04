#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct rtsx_pcr {TYPE_1__* ops; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* full_on ) (struct rtsx_pcr*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  rtsx_comm_pm_full_on (struct rtsx_pcr*) ; 
 int /*<<< orphan*/  stub1 (struct rtsx_pcr*) ; 

__attribute__((used)) static void rtsx_pm_full_on(struct rtsx_pcr *pcr)
{
	if (pcr->ops->full_on)
		pcr->ops->full_on(pcr);
	else
		rtsx_comm_pm_full_on(pcr);
}
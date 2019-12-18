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
struct TYPE_2__ {int /*<<< orphan*/  (* set_aspm ) (struct rtsx_pcr*,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  rtsx_comm_set_aspm (struct rtsx_pcr*,int) ; 
 int /*<<< orphan*/  stub1 (struct rtsx_pcr*,int) ; 

__attribute__((used)) static void rtsx_disable_aspm(struct rtsx_pcr *pcr)
{
	if (pcr->ops->set_aspm)
		pcr->ops->set_aspm(pcr, false);
	else
		rtsx_comm_set_aspm(pcr, false);
}
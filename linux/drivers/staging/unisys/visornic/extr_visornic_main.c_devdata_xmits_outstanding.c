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
struct TYPE_2__ {scalar_t__ sent_xmit; scalar_t__ got_xmit_done; } ;
struct visornic_devdata {TYPE_1__ chstat; } ;

/* Variables and functions */
 unsigned long ULONG_MAX ; 

__attribute__((used)) static unsigned long devdata_xmits_outstanding(struct visornic_devdata *devdata)
{
	if (devdata->chstat.sent_xmit >= devdata->chstat.got_xmit_done)
		return devdata->chstat.sent_xmit -
			devdata->chstat.got_xmit_done;
	return (ULONG_MAX - devdata->chstat.got_xmit_done
		+ devdata->chstat.sent_xmit + 1);
}
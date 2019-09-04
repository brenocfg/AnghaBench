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
struct qib_pportdata {TYPE_1__* dd; } ;
struct TYPE_2__ {int upd_pio_shadow; } ;

/* Variables and functions */
 int QIB_SENDCTRL_AVAIL_BLIP ; 
 int QIB_SENDCTRL_DISARM_ALL ; 
 int QIB_SENDCTRL_FLUSH ; 
 int /*<<< orphan*/  sendctrl_7220_mod (struct qib_pportdata*,int) ; 

__attribute__((used)) static void qib_7220_sdma_hw_clean_up(struct qib_pportdata *ppd)
{
	/* This will trigger the Abort interrupt */
	sendctrl_7220_mod(ppd, QIB_SENDCTRL_DISARM_ALL | QIB_SENDCTRL_FLUSH |
			  QIB_SENDCTRL_AVAIL_BLIP);
	ppd->dd->upd_pio_shadow  = 1; /* update our idea of what's busy */
}
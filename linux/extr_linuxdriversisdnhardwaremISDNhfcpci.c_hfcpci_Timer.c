#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct timer_list {int dummy; } ;
struct TYPE_4__ {scalar_t__ expires; } ;
struct TYPE_5__ {TYPE_1__ timer; } ;
struct hfc_pci {TYPE_2__ hw; } ;
struct TYPE_6__ {int /*<<< orphan*/  timer; } ;

/* Variables and functions */
 struct hfc_pci* from_timer (int /*<<< orphan*/ ,struct timer_list*,int /*<<< orphan*/ ) ; 
 struct hfc_pci* hc ; 
 TYPE_3__ hw ; 
 scalar_t__ jiffies ; 

__attribute__((used)) static void
hfcpci_Timer(struct timer_list *t)
{
	struct hfc_pci *hc = from_timer(hc, t, hw.timer);
	hc->hw.timer.expires = jiffies + 75;
	/* WD RESET */
/*
 *	WriteReg(hc, HFCD_DATA, HFCD_CTMT, hc->hw.ctmt | 0x80);
 *	add_timer(&hc->hw.timer);
 */
}
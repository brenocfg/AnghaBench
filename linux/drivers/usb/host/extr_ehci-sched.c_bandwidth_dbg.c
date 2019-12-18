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
struct ehci_per_sched {int bw_phase; int /*<<< orphan*/  cs_mask; int /*<<< orphan*/  c_usecs; int /*<<< orphan*/  usecs; int /*<<< orphan*/  period; scalar_t__ phase_uf; int /*<<< orphan*/  phase; int /*<<< orphan*/  bw_uperiod; TYPE_3__* ep; TYPE_1__* udev; } ;
struct ehci_hcd {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  bEndpointAddress; } ;
struct TYPE_6__ {TYPE_2__ desc; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,char*,char*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void bandwidth_dbg(struct ehci_hcd *ehci, int sign, char *type,
		struct ehci_per_sched *ps)
{
	dev_dbg(&ps->udev->dev,
			"ep %02x: %s %s @ %u+%u (%u.%u+%u) [%u/%u us] mask %04x\n",
			ps->ep->desc.bEndpointAddress,
			(sign >= 0 ? "reserve" : "release"), type,
			(ps->bw_phase << 3) + ps->phase_uf, ps->bw_uperiod,
			ps->phase, ps->phase_uf, ps->period,
			ps->usecs, ps->c_usecs, ps->cs_mask);
}
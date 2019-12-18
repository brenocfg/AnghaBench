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
struct ehci_tt {int* bandwidth; int /*<<< orphan*/  ps_list; } ;
struct TYPE_2__ {int usecs; int c_usecs; int tt_usecs; scalar_t__ phase; int bw_phase; unsigned int phase_uf; unsigned int cs_mask; scalar_t__ bw_period; int /*<<< orphan*/  ps_list; int /*<<< orphan*/  udev; scalar_t__ bw_uperiod; } ;
struct ehci_qh {TYPE_1__ ps; } ;
struct ehci_hcd {int* bandwidth; } ;

/* Variables and functions */
 unsigned int EHCI_BANDWIDTH_FRAMES ; 
 unsigned int EHCI_BANDWIDTH_SIZE ; 
 scalar_t__ NO_FRAME ; 
 int /*<<< orphan*/  bandwidth_dbg (struct ehci_hcd*,int,char*,TYPE_1__*) ; 
 struct ehci_tt* find_tt (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void reserve_release_intr_bandwidth(struct ehci_hcd *ehci,
		struct ehci_qh *qh, int sign)
{
	unsigned		start_uf;
	unsigned		i, j, m;
	int			usecs = qh->ps.usecs;
	int			c_usecs = qh->ps.c_usecs;
	int			tt_usecs = qh->ps.tt_usecs;
	struct ehci_tt		*tt;

	if (qh->ps.phase == NO_FRAME)	/* Bandwidth wasn't reserved */
		return;
	start_uf = qh->ps.bw_phase << 3;

	bandwidth_dbg(ehci, sign, "intr", &qh->ps);

	if (sign < 0) {		/* Release bandwidth */
		usecs = -usecs;
		c_usecs = -c_usecs;
		tt_usecs = -tt_usecs;
	}

	/* Entire transaction (high speed) or start-split (full/low speed) */
	for (i = start_uf + qh->ps.phase_uf; i < EHCI_BANDWIDTH_SIZE;
			i += qh->ps.bw_uperiod)
		ehci->bandwidth[i] += usecs;

	/* Complete-split (full/low speed) */
	if (qh->ps.c_usecs) {
		/* NOTE: adjustments needed for FSTN */
		for (i = start_uf; i < EHCI_BANDWIDTH_SIZE;
				i += qh->ps.bw_uperiod) {
			for ((j = 2, m = 1 << (j+8)); j < 8; (++j, m <<= 1)) {
				if (qh->ps.cs_mask & m)
					ehci->bandwidth[i+j] += c_usecs;
			}
		}
	}

	/* FS/LS bus bandwidth */
	if (tt_usecs) {
		tt = find_tt(qh->ps.udev);
		if (sign > 0)
			list_add_tail(&qh->ps.ps_list, &tt->ps_list);
		else
			list_del(&qh->ps.ps_list);

		for (i = start_uf >> 3; i < EHCI_BANDWIDTH_FRAMES;
				i += qh->ps.bw_period)
			tt->bandwidth[i] += tt_usecs;
	}
}
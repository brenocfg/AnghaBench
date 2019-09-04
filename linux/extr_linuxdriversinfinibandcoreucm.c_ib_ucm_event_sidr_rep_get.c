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
struct ib_ucm_sidr_rep_event_resp {int /*<<< orphan*/  qpn; int /*<<< orphan*/  qkey; int /*<<< orphan*/  status; } ;
struct ib_cm_sidr_rep_event_param {int /*<<< orphan*/  qpn; int /*<<< orphan*/  qkey; int /*<<< orphan*/  status; } ;

/* Variables and functions */

__attribute__((used)) static void ib_ucm_event_sidr_rep_get(struct ib_ucm_sidr_rep_event_resp *urep,
				      const struct ib_cm_sidr_rep_event_param *krep)
{
	urep->status = krep->status;
	urep->qkey   = krep->qkey;
	urep->qpn    = krep->qpn;
}
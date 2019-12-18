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
struct tg3 {scalar_t__ ptp_adjust; int /*<<< orphan*/ * ptp_clock; } ;

/* Variables and functions */
 int /*<<< orphan*/  PTP_CAPABLE ; 
 int /*<<< orphan*/  ptp_clock_unregister (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tg3_flag (struct tg3*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void tg3_ptp_fini(struct tg3 *tp)
{
	if (!tg3_flag(tp, PTP_CAPABLE) || !tp->ptp_clock)
		return;

	ptp_clock_unregister(tp->ptp_clock);
	tp->ptp_clock = NULL;
	tp->ptp_adjust = 0;
}
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
struct qib_pportdata {unsigned long long sdma_descq_cnt; int /*<<< orphan*/  dd; } ;

/* Variables and functions */
 unsigned long long QIB_7220_SendDmaLenGen_Generation_MSB ; 
 int /*<<< orphan*/  kr_senddmalengen ; 
 int /*<<< orphan*/  qib_write_kreg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned long long) ; 

__attribute__((used)) static void qib_sdma_7220_setlengen(struct qib_pportdata *ppd)
{
	/*
	 * Set SendDmaLenGen and clear and set
	 * the MSB of the generation count to enable generation checking
	 * and load the internal generation counter.
	 */
	qib_write_kreg(ppd->dd, kr_senddmalengen, ppd->sdma_descq_cnt);
	qib_write_kreg(ppd->dd, kr_senddmalengen,
		       ppd->sdma_descq_cnt |
		       (1ULL << QIB_7220_SendDmaLenGen_Generation_MSB));
}
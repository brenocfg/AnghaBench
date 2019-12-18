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
typedef  int /*<<< orphan*/  u16 ;
struct qib_pportdata {int /*<<< orphan*/  sdma_descq_tail; } ;

/* Variables and functions */
 int /*<<< orphan*/  krp_senddmatail ; 
 int /*<<< orphan*/  qib_write_kreg_port (struct qib_pportdata*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wmb () ; 

__attribute__((used)) static void qib_sdma_update_7322_tail(struct qib_pportdata *ppd, u16 tail)
{
	/* Commit writes to memory and advance the tail on the chip */
	wmb();
	ppd->sdma_descq_tail = tail;
	qib_write_kreg_port(ppd, krp_senddmatail, tail);
}
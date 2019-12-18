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
typedef  int u64 ;
struct qib_pportdata {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  HaltInProg ; 
 int /*<<< orphan*/  InternalSDmaHalt ; 
 int SYM_MASK (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ScbEmpty ; 
 int /*<<< orphan*/  ScoreBoardDrainInProg ; 
 int /*<<< orphan*/  SendDmaStatus_0 ; 
 int /*<<< orphan*/  krp_senddmastatus ; 
 int qib_read_kreg_port (struct qib_pportdata*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int qib_sdma_7322_busy(struct qib_pportdata *ppd)
{
	u64 hwstatus = qib_read_kreg_port(ppd, krp_senddmastatus);

	return (hwstatus & SYM_MASK(SendDmaStatus_0, ScoreBoardDrainInProg)) ||
	       (hwstatus & SYM_MASK(SendDmaStatus_0, HaltInProg)) ||
	       !(hwstatus & SYM_MASK(SendDmaStatus_0, InternalSDmaHalt)) ||
	       !(hwstatus & SYM_MASK(SendDmaStatus_0, ScbEmpty));
}
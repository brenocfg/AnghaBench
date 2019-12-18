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
typedef  int uint8_t ;
struct MessageUnit_D {int /*<<< orphan*/  inbound_msgaddr0; } ;
struct AdapterControlBlock {TYPE_1__* host; struct MessageUnit_D* pmuD; } ;
struct TYPE_2__ {int /*<<< orphan*/  host_no; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARCMSR_INBOUND_MESG0_ABORT_CMD ; 
 int /*<<< orphan*/  arcmsr_hbaD_wait_msgint_ready (struct AdapterControlBlock*) ; 
 int /*<<< orphan*/  pr_notice (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static uint8_t arcmsr_hbaD_abort_allcmd(struct AdapterControlBlock *pACB)
{
	struct MessageUnit_D *reg = pACB->pmuD;

	writel(ARCMSR_INBOUND_MESG0_ABORT_CMD, reg->inbound_msgaddr0);
	if (!arcmsr_hbaD_wait_msgint_ready(pACB)) {
		pr_notice("arcmsr%d: wait 'abort all outstanding "
			"command' timeout\n", pACB->host->host_no);
		return false;
	}
	return true;
}
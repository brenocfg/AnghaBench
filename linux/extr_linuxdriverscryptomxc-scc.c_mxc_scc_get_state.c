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
struct mxc_scc {scalar_t__ base; } ;
typedef  enum mxc_scc_state { ____Placeholder_mxc_scc_state } mxc_scc_state ;

/* Variables and functions */
 scalar_t__ SCC_SMN_SEQ_CHECK ; 
 scalar_t__ SCC_SMN_SEQ_END ; 
 scalar_t__ SCC_SMN_SEQ_START ; 
#define  SCC_SMN_STATE_FAIL 130 
 int SCC_SMN_STATE_HEALTH_CHECK ; 
#define  SCC_SMN_STATE_NON_SECURE 129 
#define  SCC_SMN_STATE_SECURE 128 
 scalar_t__ SCC_SMN_STATUS ; 
 int SCC_SMN_STATUS_STATE_MASK ; 
 int SCC_STATE_FAILED ; 
 int SCC_STATE_OK ; 
 int SCC_STATE_UNIMPLEMENTED ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static enum mxc_scc_state mxc_scc_get_state(struct mxc_scc *scc)
{
	enum mxc_scc_state state;
	int status;

	status = readl(scc->base + SCC_SMN_STATUS) &
		       SCC_SMN_STATUS_STATE_MASK;

	/* If in Health Check, try to bringup to secure state */
	if (status & SCC_SMN_STATE_HEALTH_CHECK) {
		/*
		 * Write a simple algorithm to the Algorithm Sequence
		 * Checker (ASC)
		 */
		writel(0xaaaa, scc->base + SCC_SMN_SEQ_START);
		writel(0x5555, scc->base + SCC_SMN_SEQ_END);
		writel(0x5555, scc->base + SCC_SMN_SEQ_CHECK);

		status = readl(scc->base + SCC_SMN_STATUS) &
			       SCC_SMN_STATUS_STATE_MASK;
	}

	switch (status) {
	case SCC_SMN_STATE_NON_SECURE:
	case SCC_SMN_STATE_SECURE:
		state = SCC_STATE_OK;
		break;
	case SCC_SMN_STATE_FAIL:
		state = SCC_STATE_FAILED;
		break;
	default:
		state = SCC_STATE_UNIMPLEMENTED;
		break;
	}

	return state;
}
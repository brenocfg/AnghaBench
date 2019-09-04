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
struct xc {scalar_t__ xpec_base; scalar_t__ xmac_base; } ;

/* Variables and functions */
 scalar_t__ NETX_XMAC_RPU_HOLD_PC_OFS ; 
 scalar_t__ NETX_XMAC_TPU_HOLD_PC_OFS ; 
 scalar_t__ NETX_XPEC_XPU_HOLD_PC_OFS ; 
 int /*<<< orphan*/  RPU_HOLD_PC ; 
 int /*<<< orphan*/  TPU_HOLD_PC ; 
 int /*<<< orphan*/  XPU_HOLD_PC ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

int xc_stop(struct xc *x)
{
	writel(RPU_HOLD_PC, x->xmac_base + NETX_XMAC_RPU_HOLD_PC_OFS);
	writel(TPU_HOLD_PC, x->xmac_base + NETX_XMAC_TPU_HOLD_PC_OFS);
	writel(XPU_HOLD_PC, x->xpec_base + NETX_XPEC_XPU_HOLD_PC_OFS);
	return 0;
}
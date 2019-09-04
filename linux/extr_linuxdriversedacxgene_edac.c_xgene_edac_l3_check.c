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
typedef  int u32 ;
struct xgene_edac_dev_ctx {int version; scalar_t__ dev_csr; } ;
struct edac_device_ctl_info {int /*<<< orphan*/  ctl_name; int /*<<< orphan*/  dev; struct xgene_edac_dev_ctx* pvt_info; } ;

/* Variables and functions */
 scalar_t__ L3C_AELR ; 
 scalar_t__ L3C_BELR ; 
 int /*<<< orphan*/  L3C_BELR_BANK (int) ; 
 scalar_t__ L3C_ELR ; 
 int /*<<< orphan*/  L3C_ELR_AGENTID (int) ; 
 int /*<<< orphan*/  L3C_ELR_ERRGRP (int) ; 
 int /*<<< orphan*/  L3C_ELR_ERRSYN (int) ; 
 int /*<<< orphan*/  L3C_ELR_ERRWAY (int) ; 
 int /*<<< orphan*/  L3C_ELR_OPTYPE (int) ; 
 int L3C_ELR_PADDRHIGH (int) ; 
 scalar_t__ L3C_ESR ; 
 int L3C_ESR_CERR_MASK ; 
 int L3C_ESR_DATATAG_MASK ; 
 int L3C_ESR_MULTIHIT_MASK ; 
 int L3C_ESR_MULTIUCERR_MASK ; 
 int L3C_ESR_UCERR_MASK ; 
 int L3C_ESR_UCEVICT_MASK ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  edac_device_handle_ce (struct edac_device_ctl_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  edac_device_handle_ue (struct edac_device_ctl_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ xgene_edac_l3_promote_to_uc_err (int,int) ; 

__attribute__((used)) static void xgene_edac_l3_check(struct edac_device_ctl_info *edac_dev)
{
	struct xgene_edac_dev_ctx *ctx = edac_dev->pvt_info;
	u32 l3cesr;
	u32 l3celr;
	u32 l3caelr;
	u32 l3cbelr;

	l3cesr = readl(ctx->dev_csr + L3C_ESR);
	if (!(l3cesr & (L3C_ESR_UCERR_MASK | L3C_ESR_CERR_MASK)))
		return;

	if (l3cesr & L3C_ESR_UCERR_MASK)
		dev_err(edac_dev->dev, "L3C uncorrectable error\n");
	if (l3cesr & L3C_ESR_CERR_MASK)
		dev_warn(edac_dev->dev, "L3C correctable error\n");

	l3celr = readl(ctx->dev_csr + L3C_ELR);
	l3caelr = readl(ctx->dev_csr + L3C_AELR);
	l3cbelr = readl(ctx->dev_csr + L3C_BELR);
	if (l3cesr & L3C_ESR_MULTIHIT_MASK)
		dev_err(edac_dev->dev, "L3C multiple hit error\n");
	if (l3cesr & L3C_ESR_UCEVICT_MASK)
		dev_err(edac_dev->dev,
			"L3C dropped eviction of line with error\n");
	if (l3cesr & L3C_ESR_MULTIUCERR_MASK)
		dev_err(edac_dev->dev, "L3C multiple uncorrectable error\n");
	if (l3cesr & L3C_ESR_DATATAG_MASK)
		dev_err(edac_dev->dev,
			"L3C data error syndrome 0x%X group 0x%X\n",
			L3C_ELR_ERRSYN(l3celr), L3C_ELR_ERRGRP(l3celr));
	else
		dev_err(edac_dev->dev,
			"L3C tag error syndrome 0x%X Way of Tag 0x%X Agent ID 0x%X Operation type 0x%X\n",
			L3C_ELR_ERRSYN(l3celr), L3C_ELR_ERRWAY(l3celr),
			L3C_ELR_AGENTID(l3celr), L3C_ELR_OPTYPE(l3celr));
	/*
	 * NOTE: Address [41:38] in L3C_ELR_PADDRHIGH(l3celr).
	 *       Address [37:6] in l3caelr. Lower 6 bits are zero.
	 */
	dev_err(edac_dev->dev, "L3C error address 0x%08X.%08X bank %d\n",
		L3C_ELR_PADDRHIGH(l3celr) << 6 | (l3caelr >> 26),
		(l3caelr & 0x3FFFFFFF) << 6, L3C_BELR_BANK(l3cbelr));
	dev_err(edac_dev->dev,
		"L3C error status register value 0x%X\n", l3cesr);

	/* Clear L3C error interrupt */
	writel(0, ctx->dev_csr + L3C_ESR);

	if (ctx->version <= 1 &&
	    xgene_edac_l3_promote_to_uc_err(l3cesr, l3celr)) {
		edac_device_handle_ue(edac_dev, 0, 0, edac_dev->ctl_name);
		return;
	}
	if (l3cesr & L3C_ESR_CERR_MASK)
		edac_device_handle_ce(edac_dev, 0, 0, edac_dev->ctl_name);
	if (l3cesr & L3C_ESR_UCERR_MASK)
		edac_device_handle_ue(edac_dev, 0, 0, edac_dev->ctl_name);
}
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
struct xgene_rng_dev {scalar_t__ csr_base; } ;

/* Variables and functions */
 scalar_t__ RNG_ALARMMASK ; 
 scalar_t__ RNG_ALARMSTOP ; 
 scalar_t__ RNG_FRODETUNE ; 
 scalar_t__ RNG_FROENABLE ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static void xgene_rng_init_fro(struct xgene_rng_dev *ctx, u32 fro_val)
{
	writel(fro_val, ctx->csr_base + RNG_FRODETUNE);
	writel(0x00000000, ctx->csr_base + RNG_ALARMMASK);
	writel(0x00000000, ctx->csr_base + RNG_ALARMSTOP);
	writel(0xFFFFFFFF, ctx->csr_base + RNG_FROENABLE);
}
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
struct sun4i_dma_promise {int /*<<< orphan*/  cfg; int /*<<< orphan*/  len; int /*<<< orphan*/  dst; int /*<<< orphan*/  src; int /*<<< orphan*/  para; } ;
struct sun4i_dma_pchan {scalar_t__ base; scalar_t__ is_dedicated; } ;

/* Variables and functions */
 scalar_t__ SUN4I_DDMA_BYTE_COUNT_REG ; 
 scalar_t__ SUN4I_DDMA_CFG_REG ; 
 scalar_t__ SUN4I_DDMA_DST_ADDR_REG ; 
 scalar_t__ SUN4I_DDMA_PARA_REG ; 
 scalar_t__ SUN4I_DDMA_SRC_ADDR_REG ; 
 scalar_t__ SUN4I_NDMA_BYTE_COUNT_REG ; 
 scalar_t__ SUN4I_NDMA_CFG_REG ; 
 scalar_t__ SUN4I_NDMA_DST_ADDR_REG ; 
 scalar_t__ SUN4I_NDMA_SRC_ADDR_REG ; 
 int /*<<< orphan*/  writel_relaxed (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void configure_pchan(struct sun4i_dma_pchan *pchan,
			    struct sun4i_dma_promise *d)
{
	/*
	 * Configure addresses and misc parameters depending on type
	 * SUN4I_DDMA has an extra field with timing parameters
	 */
	if (pchan->is_dedicated) {
		writel_relaxed(d->src, pchan->base + SUN4I_DDMA_SRC_ADDR_REG);
		writel_relaxed(d->dst, pchan->base + SUN4I_DDMA_DST_ADDR_REG);
		writel_relaxed(d->len, pchan->base + SUN4I_DDMA_BYTE_COUNT_REG);
		writel_relaxed(d->para, pchan->base + SUN4I_DDMA_PARA_REG);
		writel_relaxed(d->cfg, pchan->base + SUN4I_DDMA_CFG_REG);
	} else {
		writel_relaxed(d->src, pchan->base + SUN4I_NDMA_SRC_ADDR_REG);
		writel_relaxed(d->dst, pchan->base + SUN4I_NDMA_DST_ADDR_REG);
		writel_relaxed(d->len, pchan->base + SUN4I_NDMA_BYTE_COUNT_REG);
		writel_relaxed(d->cfg, pchan->base + SUN4I_NDMA_CFG_REG);
	}
}
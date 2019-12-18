#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
struct TYPE_3__ {scalar_t__ dma_offset; scalar_t__* hw_addr_ptr; scalar_t__ dma_low; scalar_t__ dma_high; scalar_t__ agpAddr; } ;
typedef  TYPE_1__ drm_via_private_t ;

/* Variables and functions */

__attribute__((used)) static uint32_t via_cmdbuf_space(drm_via_private_t *dev_priv)
{
	uint32_t agp_base = dev_priv->dma_offset + (uint32_t) dev_priv->agpAddr;
	uint32_t hw_addr = *(dev_priv->hw_addr_ptr) - agp_base;

	return ((hw_addr <= dev_priv->dma_low) ?
		(dev_priv->dma_high + hw_addr - dev_priv->dma_low) :
		(hw_addr - dev_priv->dma_low));
}
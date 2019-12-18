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
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_3__ {scalar_t__ dma_low; scalar_t__ dma_ptr; } ;
typedef  TYPE_1__ drm_via_private_t ;

/* Variables and functions */

__attribute__((used)) static inline uint32_t *via_get_dma(drm_via_private_t *dev_priv)
{
	return (uint32_t *) (dev_priv->dma_ptr + dev_priv->dma_low);
}
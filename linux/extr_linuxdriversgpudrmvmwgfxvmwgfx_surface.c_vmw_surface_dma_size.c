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
typedef  int uint32_t ;
struct vmw_surface_dma {int dummy; } ;
struct vmw_surface {int num_sizes; } ;

/* Variables and functions */

__attribute__((used)) static inline uint32_t vmw_surface_dma_size(const struct vmw_surface *srf)
{
	return srf->num_sizes * sizeof(struct vmw_surface_dma);
}
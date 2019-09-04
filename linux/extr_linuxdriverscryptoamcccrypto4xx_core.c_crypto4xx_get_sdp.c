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
struct crypto4xx_device {struct ce_sd* sdr; scalar_t__ sdr_pa; } ;
struct ce_sd {int dummy; } ;
typedef  scalar_t__ dma_addr_t ;

/* Variables and functions */

__attribute__((used)) static inline struct ce_sd *crypto4xx_get_sdp(struct crypto4xx_device *dev,
					      dma_addr_t *sd_dma, u32 idx)
{
	*sd_dma = dev->sdr_pa + sizeof(struct ce_sd) * idx;

	return &dev->sdr[idx];
}
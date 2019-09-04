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
struct kernel_param {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  TW686X_DMA_MODE_CONTIG ; 
 int /*<<< orphan*/  TW686X_DMA_MODE_MEMCPY ; 
 int /*<<< orphan*/  TW686X_DMA_MODE_SG ; 
 int /*<<< orphan*/  dma_mode ; 
 int /*<<< orphan*/  dma_mode_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcasecmp (char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int tw686x_dma_mode_set(const char *val, const struct kernel_param *kp)
{
	if (!strcasecmp(val, dma_mode_name(TW686X_DMA_MODE_MEMCPY)))
		dma_mode = TW686X_DMA_MODE_MEMCPY;
	else if (!strcasecmp(val, dma_mode_name(TW686X_DMA_MODE_CONTIG)))
		dma_mode = TW686X_DMA_MODE_CONTIG;
	else if (!strcasecmp(val, dma_mode_name(TW686X_DMA_MODE_SG)))
		dma_mode = TW686X_DMA_MODE_SG;
	else
		return -EINVAL;
	return 0;
}
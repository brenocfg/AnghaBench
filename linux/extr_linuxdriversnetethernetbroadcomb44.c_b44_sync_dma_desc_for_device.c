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
struct ssb_device {int /*<<< orphan*/  dma_dev; } ;
typedef  enum dma_data_direction { ____Placeholder_dma_data_direction } dma_data_direction ;
typedef  scalar_t__ dma_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  dma_desc_sync_size ; 
 int /*<<< orphan*/  dma_sync_single_for_device (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline void b44_sync_dma_desc_for_device(struct ssb_device *sdev,
						dma_addr_t dma_base,
						unsigned long offset,
						enum dma_data_direction dir)
{
	dma_sync_single_for_device(sdev->dma_dev, dma_base + offset,
				   dma_desc_sync_size, dir);
}
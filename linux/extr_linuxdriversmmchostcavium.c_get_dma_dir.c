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
struct mmc_data {int flags; } ;

/* Variables and functions */
 int DMA_FROM_DEVICE ; 
 int DMA_TO_DEVICE ; 
 int MMC_DATA_WRITE ; 

__attribute__((used)) static int get_dma_dir(struct mmc_data *data)
{
	return (data->flags & MMC_DATA_WRITE) ? DMA_TO_DEVICE : DMA_FROM_DEVICE;
}
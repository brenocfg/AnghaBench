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
struct atmel_aes_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_DEV_TO_MEM ; 
 int /*<<< orphan*/  DMA_MEM_TO_DEV ; 
 int /*<<< orphan*/  atmel_aes_dma_transfer_stop (struct atmel_aes_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atmel_aes_unmap (struct atmel_aes_dev*) ; 

__attribute__((used)) static void atmel_aes_dma_stop(struct atmel_aes_dev *dd)
{
	atmel_aes_dma_transfer_stop(dd, DMA_MEM_TO_DEV);
	atmel_aes_dma_transfer_stop(dd, DMA_DEV_TO_MEM);
	atmel_aes_unmap(dd);
}
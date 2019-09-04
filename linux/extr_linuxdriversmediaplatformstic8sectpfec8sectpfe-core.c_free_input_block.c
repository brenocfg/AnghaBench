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
struct channel_info {int /*<<< orphan*/  pid_buffer_start; scalar_t__ pid_buffer_busaddr; int /*<<< orphan*/  back_buffer_start; scalar_t__ back_buffer_busaddr; } ;
struct c8sectpfei {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_BIDIRECTIONAL ; 
 int /*<<< orphan*/  FEI_BUFFER_SIZE ; 
 int /*<<< orphan*/  PID_TABLE_SIZE ; 
 int /*<<< orphan*/  dma_mapping_error (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  dma_unmap_single (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void free_input_block(struct c8sectpfei *fei, struct channel_info *tsin)
{
	if (!fei || !tsin)
		return;

	if (tsin->back_buffer_busaddr)
		if (!dma_mapping_error(fei->dev, tsin->back_buffer_busaddr))
			dma_unmap_single(fei->dev, tsin->back_buffer_busaddr,
				FEI_BUFFER_SIZE, DMA_BIDIRECTIONAL);

	kfree(tsin->back_buffer_start);

	if (tsin->pid_buffer_busaddr)
		if (!dma_mapping_error(fei->dev, tsin->pid_buffer_busaddr))
			dma_unmap_single(fei->dev, tsin->pid_buffer_busaddr,
				PID_TABLE_SIZE, DMA_BIDIRECTIONAL);

	kfree(tsin->pid_buffer_start);
}
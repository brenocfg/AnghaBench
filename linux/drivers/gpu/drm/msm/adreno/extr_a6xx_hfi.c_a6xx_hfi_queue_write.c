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
typedef  scalar_t__ u32 ;
struct a6xx_hfi_queue_header {scalar_t__ write_index; scalar_t__ size; int /*<<< orphan*/  dropped; int /*<<< orphan*/  read_index; } ;
struct a6xx_hfi_queue {int /*<<< orphan*/  lock; scalar_t__* data; struct a6xx_hfi_queue_header* header; } ;
struct a6xx_gmu {int dummy; } ;

/* Variables and functions */
 scalar_t__ CIRC_SPACE (scalar_t__,int /*<<< orphan*/ ,scalar_t__) ; 
 int ENOSPC ; 
 int /*<<< orphan*/  REG_A6XX_GMU_HOST2GMU_INTR_SET ; 
 int /*<<< orphan*/  gmu_write (struct a6xx_gmu*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int a6xx_hfi_queue_write(struct a6xx_gmu *gmu,
	struct a6xx_hfi_queue *queue, u32 *data, u32 dwords)
{
	struct a6xx_hfi_queue_header *header = queue->header;
	u32 i, space, index = header->write_index;

	spin_lock(&queue->lock);

	space = CIRC_SPACE(header->write_index, header->read_index,
		header->size);
	if (space < dwords) {
		header->dropped++;
		spin_unlock(&queue->lock);
		return -ENOSPC;
	}

	for (i = 0; i < dwords; i++) {
		queue->data[index] = data[i];
		index = (index + 1) % header->size;
	}

	header->write_index = index;
	spin_unlock(&queue->lock);

	gmu_write(gmu, REG_A6XX_GMU_HOST2GMU_INTR_SET, 0x01);
	return 0;
}
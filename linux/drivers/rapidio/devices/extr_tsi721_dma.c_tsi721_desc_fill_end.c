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
struct tsi721_dma_desc {int /*<<< orphan*/  bcount; int /*<<< orphan*/  type_id; } ;

/* Variables and functions */
 int EINVAL ; 
 int TSI721_DMAD_BCOUNT1 ; 
 int TSI721_DMAD_IOF ; 
 int /*<<< orphan*/  cpu_to_le32 (int) ; 

__attribute__((used)) static int
tsi721_desc_fill_end(struct tsi721_dma_desc *bd_ptr, u32 bcount, bool interrupt)
{
	if (!bd_ptr)
		return -EINVAL;

	/* Update DMA descriptor */
	if (interrupt)
		bd_ptr->type_id |= cpu_to_le32(TSI721_DMAD_IOF);
	bd_ptr->bcount |= cpu_to_le32(bcount & TSI721_DMAD_BCOUNT1);

	return 0;
}
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
struct ioatdma_chan {int alloc_order; } ;

/* Variables and functions */

__attribute__((used)) static inline u32 ioat_ring_size(struct ioatdma_chan *ioat_chan)
{
	return 1 << ioat_chan->alloc_order;
}
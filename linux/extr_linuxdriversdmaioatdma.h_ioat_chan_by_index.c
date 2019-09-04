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
struct ioatdma_device {struct ioatdma_chan** idx; } ;
struct ioatdma_chan {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static inline struct ioatdma_chan *
ioat_chan_by_index(struct ioatdma_device *ioat_dma, int index)
{
	return ioat_dma->idx[index];
}
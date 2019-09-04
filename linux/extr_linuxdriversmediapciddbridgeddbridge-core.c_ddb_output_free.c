#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct ddb_output {TYPE_1__* dma; } ;
typedef  int s32 ;
struct TYPE_2__ {int stat; int cbuf; int num; int size; int coff; } ;

/* Variables and functions */

__attribute__((used)) static u32 ddb_output_free(struct ddb_output *output)
{
	u32 idx, off, stat = output->dma->stat;
	s32 diff;

	idx = (stat >> 11) & 0x1f;
	off = (stat & 0x7ff) << 7;

	if (output->dma->cbuf != idx) {
		if ((((output->dma->cbuf + 1) % output->dma->num) == idx) &&
		    (output->dma->size - output->dma->coff <= (2 * 188)))
			return 0;
		return 188;
	}
	diff = off - output->dma->coff;
	if (diff <= 0 || diff > (2 * 188))
		return 188;
	return 0;
}
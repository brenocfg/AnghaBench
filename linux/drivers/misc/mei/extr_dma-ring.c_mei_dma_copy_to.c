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
struct mei_device {TYPE_1__* dr_dscr; } ;
struct TYPE_2__ {unsigned char* vaddr; } ;

/* Variables and functions */
 size_t DMA_DSCR_HOST ; 
 int /*<<< orphan*/  memcpy (unsigned char*,unsigned char*,size_t) ; 

__attribute__((used)) static size_t mei_dma_copy_to(struct mei_device *dev, unsigned char *buf,
			      u32 offset, u32 n)
{
	unsigned char *hbuf = dev->dr_dscr[DMA_DSCR_HOST].vaddr;

	size_t b_offset = offset << 2;
	size_t b_n = n << 2;

	memcpy(hbuf + b_offset, buf, b_n);

	return b_n;
}
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
struct kvaser_pciefd {int dummy; } ;

/* Variables and functions */
 int KVASER_PCIEFD_DMA_SIZE ; 
 int kvaser_pciefd_read_packet (struct kvaser_pciefd*,int*,int) ; 

__attribute__((used)) static int kvaser_pciefd_read_buffer(struct kvaser_pciefd *pcie, int dma_buf)
{
	int pos = 0;
	int res = 0;

	do {
		res = kvaser_pciefd_read_packet(pcie, &pos, dma_buf);
	} while (!res && pos > 0 && pos < KVASER_PCIEFD_DMA_SIZE);

	return res;
}
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
struct sge {size_t jumbo_fl; TYPE_1__* freelQ; } ;
struct cpl_rx_data {int dummy; } ;
struct TYPE_2__ {unsigned int rx_buffer_size; unsigned int dma_offset; } ;

/* Variables and functions */

__attribute__((used)) static inline unsigned int jumbo_payload_capacity(const struct sge *sge)
{
	return sge->freelQ[sge->jumbo_fl].rx_buffer_size -
		sge->freelQ[sge->jumbo_fl].dma_offset -
		sizeof(struct cpl_rx_data);
}
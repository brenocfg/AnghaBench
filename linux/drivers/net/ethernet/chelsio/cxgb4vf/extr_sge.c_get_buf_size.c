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
struct sge {int fl_pg_order; } ;
struct rx_sw_desc {int dma_addr; } ;
struct adapter {struct sge sge; } ;

/* Variables and functions */
 int PAGE_SIZE ; 
 int RX_LARGE_BUF ; 

__attribute__((used)) static inline int get_buf_size(const struct adapter *adapter,
			       const struct rx_sw_desc *sdesc)
{
	const struct sge *s = &adapter->sge;

	return (s->fl_pg_order > 0 && (sdesc->dma_addr & RX_LARGE_BUF)
		? (PAGE_SIZE << s->fl_pg_order) : PAGE_SIZE);
}
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
struct rx_sw_desc {unsigned int dma_addr; } ;
struct adapter {struct sge sge; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 int FL_MTU_LARGE_BUFSIZE (struct adapter*) ; 
 int FL_MTU_SMALL_BUFSIZE (struct adapter*) ; 
 int PAGE_SIZE ; 
 unsigned int RX_BUF_SIZE ; 
#define  RX_LARGE_MTU_BUF 131 
#define  RX_LARGE_PG_BUF 130 
#define  RX_SMALL_MTU_BUF 129 
#define  RX_SMALL_PG_BUF 128 

__attribute__((used)) static inline int get_buf_size(struct adapter *adapter,
			       const struct rx_sw_desc *d)
{
	struct sge *s = &adapter->sge;
	unsigned int rx_buf_size_idx = d->dma_addr & RX_BUF_SIZE;
	int buf_size;

	switch (rx_buf_size_idx) {
	case RX_SMALL_PG_BUF:
		buf_size = PAGE_SIZE;
		break;

	case RX_LARGE_PG_BUF:
		buf_size = PAGE_SIZE << s->fl_pg_order;
		break;

	case RX_SMALL_MTU_BUF:
		buf_size = FL_MTU_SMALL_BUFSIZE(adapter);
		break;

	case RX_LARGE_MTU_BUF:
		buf_size = FL_MTU_LARGE_BUFSIZE(adapter);
		break;

	default:
		BUG();
	}

	return buf_size;
}
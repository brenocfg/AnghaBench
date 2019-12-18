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
struct TYPE_2__ {int dma_addr; int /*<<< orphan*/  addr; } ;
struct ef4_special_buffer {int entries; int index; TYPE_1__ buf; } ;
struct ef4_nic {int /*<<< orphan*/  net_dev; } ;
typedef  int /*<<< orphan*/  ef4_qword_t ;
typedef  int dma_addr_t ;

/* Variables and functions */
 int EF4_BUF_SIZE ; 
 int /*<<< orphan*/  EF4_BUG_ON_PARANOID (int) ; 
 int /*<<< orphan*/  EF4_POPULATE_QWORD_3 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FRF_AZ_BUF_ADR_FBUF ; 
 int /*<<< orphan*/  FRF_AZ_BUF_ADR_REGION ; 
 int /*<<< orphan*/  FRF_AZ_BUF_OWNER_ID_FBUF ; 
 int /*<<< orphan*/  ef4_write_buf_tbl (struct ef4_nic*,int /*<<< orphan*/ *,unsigned int) ; 
 int /*<<< orphan*/  netif_dbg (struct ef4_nic*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,unsigned int,unsigned long long) ; 
 int /*<<< orphan*/  probe ; 

__attribute__((used)) static void
ef4_init_special_buffer(struct ef4_nic *efx, struct ef4_special_buffer *buffer)
{
	ef4_qword_t buf_desc;
	unsigned int index;
	dma_addr_t dma_addr;
	int i;

	EF4_BUG_ON_PARANOID(!buffer->buf.addr);

	/* Write buffer descriptors to NIC */
	for (i = 0; i < buffer->entries; i++) {
		index = buffer->index + i;
		dma_addr = buffer->buf.dma_addr + (i * EF4_BUF_SIZE);
		netif_dbg(efx, probe, efx->net_dev,
			  "mapping special buffer %d at %llx\n",
			  index, (unsigned long long)dma_addr);
		EF4_POPULATE_QWORD_3(buf_desc,
				     FRF_AZ_BUF_ADR_REGION, 0,
				     FRF_AZ_BUF_ADR_FBUF, dma_addr >> 12,
				     FRF_AZ_BUF_OWNER_ID_FBUF, 0);
		ef4_write_buf_tbl(efx, &buf_desc, index);
	}
}
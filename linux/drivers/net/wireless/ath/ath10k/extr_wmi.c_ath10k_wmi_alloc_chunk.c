#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_4__ {int num_mem_chunks; TYPE_1__* mem_chunks; } ;
struct ath10k {TYPE_2__ wmi; int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;
struct TYPE_3__ {int len; int req_id; int /*<<< orphan*/  paddr; void* vaddr; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 void* dma_alloc_coherent (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int round_up (int,int) ; 

__attribute__((used)) static int ath10k_wmi_alloc_chunk(struct ath10k *ar, u32 req_id,
				  u32 num_units, u32 unit_len)
{
	dma_addr_t paddr;
	u32 pool_size;
	int idx = ar->wmi.num_mem_chunks;
	void *vaddr;

	pool_size = num_units * round_up(unit_len, 4);
	vaddr = dma_alloc_coherent(ar->dev, pool_size, &paddr, GFP_KERNEL);

	if (!vaddr)
		return -ENOMEM;

	ar->wmi.mem_chunks[idx].vaddr = vaddr;
	ar->wmi.mem_chunks[idx].paddr = paddr;
	ar->wmi.mem_chunks[idx].len = pool_size;
	ar->wmi.mem_chunks[idx].req_id = req_id;
	ar->wmi.num_mem_chunks++;

	return num_units;
}
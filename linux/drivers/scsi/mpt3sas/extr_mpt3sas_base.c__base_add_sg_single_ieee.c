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
typedef  void* u8 ;
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  dma_addr_t ;
struct TYPE_2__ {int /*<<< orphan*/  Address; int /*<<< orphan*/  Length; void* NextChainOffset; void* Flags; } ;
typedef  TYPE_1__ Mpi25IeeeSgeChain64_t ;

/* Variables and functions */
 int /*<<< orphan*/  cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_le64 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
_base_add_sg_single_ieee(void *paddr, u8 flags, u8 chain_offset, u32 length,
	dma_addr_t dma_addr)
{
	Mpi25IeeeSgeChain64_t *sgel = paddr;

	sgel->Flags = flags;
	sgel->NextChainOffset = chain_offset;
	sgel->Length = cpu_to_le32(length);
	sgel->Address = cpu_to_le64(dma_addr);
}
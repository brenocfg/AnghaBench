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
typedef  int u32 ;

/* Variables and functions */
 int /*<<< orphan*/  AT (int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int NFP_CPP_ID (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  P32 ; 
 int /*<<< orphan*/  P64 ; 
 int nfp6000_mu_common (int) ; 

__attribute__((used)) static int nfp6000_mu_ctm(u32 cpp_id)
{
	switch (cpp_id & NFP_CPP_ID(0, ~0, ~0)) {
	AT(16, 1,   0, P32);	/* packet_read_packet_status */
	AT(17, 1,   0, P32);	/* packet_credit_get */
	AT(17, 3,   0, P64);	/* packet_add_thread */
	AT(18, 2,   0, P64);	/* packet_free_and_return_pointer */
	AT(18, 3,   0, P64);	/* packet_return_pointer */
	AT(21, 0,   0, P64);	/* pe_dma_to_memory_indirect */
	AT(21, 1,   0, P64);	/* pe_dma_to_memory_indirect_swap */
	AT(21, 2,   0, P64);	/* pe_dma_to_memory_indirect_free */
	AT(21, 3,   0, P64);	/* pe_dma_to_memory_indirect_free_swap */
	default:
		return nfp6000_mu_common(cpp_id);
	}
}
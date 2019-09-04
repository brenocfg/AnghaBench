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
typedef  unsigned int u32 ;
struct srp_map_state {unsigned int total_len; int /*<<< orphan*/  ndesc; struct srp_direct_buf* desc; } ;
struct srp_direct_buf {void* len; void* key; int /*<<< orphan*/  va; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 void* cpu_to_be32 (unsigned int) ; 
 int /*<<< orphan*/  cpu_to_be64 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void srp_map_desc(struct srp_map_state *state, dma_addr_t dma_addr,
			 unsigned int dma_len, u32 rkey)
{
	struct srp_direct_buf *desc = state->desc;

	WARN_ON_ONCE(!dma_len);

	desc->va = cpu_to_be64(dma_addr);
	desc->key = cpu_to_be32(rkey);
	desc->len = cpu_to_be32(dma_len);

	state->total_len += dma_len;
	state->desc++;
	state->ndesc++;
}
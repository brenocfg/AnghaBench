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
typedef  int /*<<< orphan*/  u64 ;
typedef  size_t u32 ;
struct ath10k_ce_pipe {TYPE_1__* ops; } ;
struct ath10k_ce {struct ath10k_ce_pipe* ce_states; } ;
struct ath10k {TYPE_2__* hw_ce_regs; } ;
struct TYPE_4__ {size_t sr_base_addr_lo; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* ce_set_src_ring_base_addr_hi ) (struct ath10k*,size_t,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 size_t ath10k_ce_base_address (struct ath10k*,size_t) ; 
 struct ath10k_ce* ath10k_ce_priv (struct ath10k*) ; 
 int /*<<< orphan*/  ath10k_ce_write32 (struct ath10k*,size_t,size_t) ; 
 size_t lower_32_bits (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct ath10k*,size_t,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void ath10k_ce_src_ring_base_addr_set(struct ath10k *ar,
						    u32 ce_id,
						    u64 addr)
{
	struct ath10k_ce *ce = ath10k_ce_priv(ar);
	struct ath10k_ce_pipe *ce_state = &ce->ce_states[ce_id];
	u32 ce_ctrl_addr = ath10k_ce_base_address(ar, ce_id);
	u32 addr_lo = lower_32_bits(addr);

	ath10k_ce_write32(ar, ce_ctrl_addr +
			  ar->hw_ce_regs->sr_base_addr_lo, addr_lo);

	if (ce_state->ops->ce_set_src_ring_base_addr_hi) {
		ce_state->ops->ce_set_src_ring_base_addr_hi(ar, ce_ctrl_addr,
							    addr);
	}
}
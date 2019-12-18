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
typedef  size_t u32 ;
struct ath10k_fw_crash_data {struct ath10k_ce_crash_data* ce_crash_data; } ;
struct ath10k_ce_crash_data {void* dst_r_idx; void* dst_wr_idx; void* src_r_idx; void* src_wr_idx; void* base_addr; } ;
struct ath10k_ce {int /*<<< orphan*/  ce_lock; } ;
struct ath10k {int /*<<< orphan*/  dump_mutex; } ;

/* Variables and functions */
 size_t CE_COUNT ; 
 size_t ath10k_ce_base_address (struct ath10k*,size_t) ; 
 size_t ath10k_ce_dest_ring_read_index_get (struct ath10k*,size_t) ; 
 size_t ath10k_ce_dest_ring_write_index_get (struct ath10k*,size_t) ; 
 struct ath10k_ce* ath10k_ce_priv (struct ath10k*) ; 
 size_t ath10k_ce_src_ring_read_index_get (struct ath10k*,size_t) ; 
 size_t ath10k_ce_src_ring_write_index_get (struct ath10k*,size_t) ; 
 int /*<<< orphan*/  ath10k_err (struct ath10k*,char*,...) ; 
 void* cpu_to_le32 (size_t) ; 
 int /*<<< orphan*/  le32_to_cpu (void*) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

void ath10k_ce_dump_registers(struct ath10k *ar,
			      struct ath10k_fw_crash_data *crash_data)
{
	struct ath10k_ce *ce = ath10k_ce_priv(ar);
	struct ath10k_ce_crash_data ce_data;
	u32 addr, id;

	lockdep_assert_held(&ar->dump_mutex);

	ath10k_err(ar, "Copy Engine register dump:\n");

	spin_lock_bh(&ce->ce_lock);
	for (id = 0; id < CE_COUNT; id++) {
		addr = ath10k_ce_base_address(ar, id);
		ce_data.base_addr = cpu_to_le32(addr);

		ce_data.src_wr_idx =
			cpu_to_le32(ath10k_ce_src_ring_write_index_get(ar, addr));
		ce_data.src_r_idx =
			cpu_to_le32(ath10k_ce_src_ring_read_index_get(ar, addr));
		ce_data.dst_wr_idx =
			cpu_to_le32(ath10k_ce_dest_ring_write_index_get(ar, addr));
		ce_data.dst_r_idx =
			cpu_to_le32(ath10k_ce_dest_ring_read_index_get(ar, addr));

		if (crash_data)
			crash_data->ce_crash_data[id] = ce_data;

		ath10k_err(ar, "[%02d]: 0x%08x %3u %3u %3u %3u", id,
			   le32_to_cpu(ce_data.base_addr),
			   le32_to_cpu(ce_data.src_wr_idx),
			   le32_to_cpu(ce_data.src_r_idx),
			   le32_to_cpu(ce_data.dst_wr_idx),
			   le32_to_cpu(ce_data.dst_r_idx));
	}

	spin_unlock_bh(&ce->ce_lock);
}
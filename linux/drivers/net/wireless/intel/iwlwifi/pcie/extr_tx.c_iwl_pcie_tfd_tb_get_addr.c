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
typedef  size_t u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct iwl_trans {TYPE_1__* trans_cfg; } ;
struct iwl_tfh_tfd {struct iwl_tfh_tb* tbs; } ;
struct iwl_tfh_tb {int /*<<< orphan*/  addr; } ;
struct iwl_tfd_tb {int /*<<< orphan*/  hi_n_len; int /*<<< orphan*/  lo; } ;
struct iwl_tfd {struct iwl_tfd_tb* tbs; } ;
typedef  int dma_addr_t ;
struct TYPE_2__ {scalar_t__ use_tfh; } ;

/* Variables and functions */
 int get_unaligned_le32 (int /*<<< orphan*/ *) ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le64_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline dma_addr_t iwl_pcie_tfd_tb_get_addr(struct iwl_trans *trans,
						  void *_tfd, u8 idx)
{

	if (trans->trans_cfg->use_tfh) {
		struct iwl_tfh_tfd *tfd = _tfd;
		struct iwl_tfh_tb *tb = &tfd->tbs[idx];

		return (dma_addr_t)(le64_to_cpu(tb->addr));
	} else {
		struct iwl_tfd *tfd = _tfd;
		struct iwl_tfd_tb *tb = &tfd->tbs[idx];
		dma_addr_t addr = get_unaligned_le32(&tb->lo);
		dma_addr_t hi_len;

		if (sizeof(dma_addr_t) <= sizeof(u32))
			return addr;

		hi_len = le16_to_cpu(tb->hi_n_len) & 0xF;

		/*
		 * shift by 16 twice to avoid warnings on 32-bit
		 * (where this code never runs anyway due to the
		 * if statement above)
		 */
		return addr | ((hi_len << 16) << 16);
	}
}
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
typedef  int u16 ;
struct iwl_trans {TYPE_1__* trans_cfg; } ;
struct iwl_tfh_tfd {struct iwl_tfh_tb* tbs; } ;
struct iwl_tfh_tb {int /*<<< orphan*/  tb_len; } ;
struct iwl_tfd_tb {int /*<<< orphan*/  hi_n_len; } ;
struct iwl_tfd {struct iwl_tfd_tb* tbs; } ;
struct TYPE_2__ {scalar_t__ use_tfh; } ;

/* Variables and functions */
 int le16_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline u16 iwl_pcie_tfd_tb_get_len(struct iwl_trans *trans, void *_tfd,
					  u8 idx)
{
	if (trans->trans_cfg->use_tfh) {
		struct iwl_tfh_tfd *tfd = _tfd;
		struct iwl_tfh_tb *tb = &tfd->tbs[idx];

		return le16_to_cpu(tb->tb_len);
	} else {
		struct iwl_tfd *tfd = _tfd;
		struct iwl_tfd_tb *tb = &tfd->tbs[idx];

		return le16_to_cpu(tb->hi_n_len) >> 4;
	}
}
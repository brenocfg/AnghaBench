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
typedef  int u8 ;
struct iwl_trans {TYPE_1__* trans_cfg; } ;
struct iwl_tfh_tfd {int /*<<< orphan*/  num_tbs; } ;
struct iwl_tfd {int num_tbs; } ;
struct TYPE_2__ {scalar_t__ use_tfh; } ;

/* Variables and functions */
 int le16_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline u8 iwl_pcie_tfd_get_num_tbs(struct iwl_trans *trans, void *_tfd)
{
	if (trans->trans_cfg->use_tfh) {
		struct iwl_tfh_tfd *tfd = _tfd;

		return le16_to_cpu(tfd->num_tbs) & 0x1f;
	} else {
		struct iwl_tfd *tfd = _tfd;

		return tfd->num_tbs & 0x1f;
	}
}
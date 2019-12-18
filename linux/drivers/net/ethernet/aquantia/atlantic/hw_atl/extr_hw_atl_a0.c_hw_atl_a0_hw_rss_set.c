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
typedef  unsigned int u8 ;
typedef  unsigned int u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct aq_rss_parameters {unsigned int* indirection_table; } ;
struct aq_hw_s {TYPE_1__* aq_nic_cfg; } ;
typedef  int /*<<< orphan*/  bitary ;
struct TYPE_2__ {int /*<<< orphan*/  num_rss_queues; } ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 unsigned int HW_ATL_A0_RSS_REDIRECTION_BITS ; 
 unsigned int HW_ATL_A0_RSS_REDIRECTION_MAX ; 
 int aq_hw_err_from_flags (struct aq_hw_s*) ; 
 int /*<<< orphan*/  hw_atl_rpf_rss_redir_tbl_addr_set (struct aq_hw_s*,unsigned int) ; 
 int /*<<< orphan*/  hw_atl_rpf_rss_redir_tbl_wr_data_set (struct aq_hw_s*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hw_atl_rpf_rss_redir_wr_en_get ; 
 int /*<<< orphan*/  hw_atl_rpf_rss_redir_wr_en_set (struct aq_hw_s*,unsigned int) ; 
 unsigned int max (unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int readx_poll_timeout_atomic (int /*<<< orphan*/ ,struct aq_hw_s*,unsigned int,int,unsigned int,unsigned int) ; 

__attribute__((used)) static int hw_atl_a0_hw_rss_set(struct aq_hw_s *self,
				struct aq_rss_parameters *rss_params)
{
	u8 *indirection_table =	rss_params->indirection_table;
	u32 i = 0U;
	u32 num_rss_queues = max(1U, self->aq_nic_cfg->num_rss_queues);
	int err = 0;
	u16 bitary[1 + (HW_ATL_A0_RSS_REDIRECTION_MAX *
		   HW_ATL_A0_RSS_REDIRECTION_BITS / 16U)];
	u32 val;

	memset(bitary, 0, sizeof(bitary));

	for (i = HW_ATL_A0_RSS_REDIRECTION_MAX; i--; ) {
		(*(u32 *)(bitary + ((i * 3U) / 16U))) |=
			((indirection_table[i] % num_rss_queues) <<
			((i * 3U) & 0xFU));
	}

	for (i = ARRAY_SIZE(bitary); i--;) {
		hw_atl_rpf_rss_redir_tbl_wr_data_set(self, bitary[i]);
		hw_atl_rpf_rss_redir_tbl_addr_set(self, i);
		hw_atl_rpf_rss_redir_wr_en_set(self, 1U);
		err = readx_poll_timeout_atomic(hw_atl_rpf_rss_redir_wr_en_get,
						self, val, val == 0,
						1000U, 10000U);
		if (err < 0)
			goto err_exit;
	}

	err = aq_hw_err_from_flags(self);

err_exit:
	return err;
}
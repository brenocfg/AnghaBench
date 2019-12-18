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
typedef  int /*<<< orphan*/  u64 ;
struct nicvf_rss_info {int enable; int cfg; int rss_size; int /*<<< orphan*/ * ind_tbl; scalar_t__ hash_bits; int /*<<< orphan*/  key; } ;
struct nicvf {int /*<<< orphan*/  rx_queues; struct nicvf_rss_info rss_info; } ;

/* Variables and functions */
 scalar_t__ CPI_ALG_NONE ; 
 int /*<<< orphan*/  NIC_VNIC_RSS_CFG ; 
 int RSS_HASH_KEY_SIZE ; 
 int RSS_IP_HASH_ENA ; 
 int RSS_TCP_HASH_ENA ; 
 int RSS_UDP_HASH_ENA ; 
 scalar_t__ cpi_alg ; 
 int /*<<< orphan*/  ethtool_rxfh_indir_default (int,int /*<<< orphan*/ ) ; 
 scalar_t__ ilog2 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netdev_rss_key_fill (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  nicvf_config_rss (struct nicvf*) ; 
 int /*<<< orphan*/  nicvf_get_rss_size (struct nicvf*) ; 
 int /*<<< orphan*/  nicvf_reg_write (struct nicvf*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  nicvf_set_rss_key (struct nicvf*) ; 
 int /*<<< orphan*/  rounddown_pow_of_two (int) ; 

__attribute__((used)) static int nicvf_rss_init(struct nicvf *nic)
{
	struct nicvf_rss_info *rss = &nic->rss_info;
	int idx;

	nicvf_get_rss_size(nic);

	if (cpi_alg != CPI_ALG_NONE) {
		rss->enable = false;
		rss->hash_bits = 0;
		return 0;
	}

	rss->enable = true;

	netdev_rss_key_fill(rss->key, RSS_HASH_KEY_SIZE * sizeof(u64));
	nicvf_set_rss_key(nic);

	rss->cfg = RSS_IP_HASH_ENA | RSS_TCP_HASH_ENA | RSS_UDP_HASH_ENA;
	nicvf_reg_write(nic, NIC_VNIC_RSS_CFG, rss->cfg);

	rss->hash_bits =  ilog2(rounddown_pow_of_two(rss->rss_size));

	for (idx = 0; idx < rss->rss_size; idx++)
		rss->ind_tbl[idx] = ethtool_rxfh_indir_default(idx,
							       nic->rx_queues);
	nicvf_config_rss(nic);
	return 1;
}
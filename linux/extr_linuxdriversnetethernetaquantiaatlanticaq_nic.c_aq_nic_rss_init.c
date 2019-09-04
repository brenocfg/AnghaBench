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
typedef  int u8 ;
struct aq_rss_parameters {int hash_secret_key_size; int indirection_table_size; int* indirection_table; int /*<<< orphan*/  hash_secret_key; } ;
struct aq_nic_cfg_s {struct aq_rss_parameters aq_rss; } ;
struct aq_nic_s {struct aq_nic_cfg_s aq_nic_cfg; } ;
typedef  int /*<<< orphan*/  rss_key ;

/* Variables and functions */
 int AQ_CFG_RSS_INDIRECTION_TABLE_MAX ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int*,int) ; 

__attribute__((used)) static void aq_nic_rss_init(struct aq_nic_s *self, unsigned int num_rss_queues)
{
	struct aq_nic_cfg_s *cfg = &self->aq_nic_cfg;
	struct aq_rss_parameters *rss_params = &cfg->aq_rss;
	int i = 0;

	static u8 rss_key[40] = {
		0x1e, 0xad, 0x71, 0x87, 0x65, 0xfc, 0x26, 0x7d,
		0x0d, 0x45, 0x67, 0x74, 0xcd, 0x06, 0x1a, 0x18,
		0xb6, 0xc1, 0xf0, 0xc7, 0xbb, 0x18, 0xbe, 0xf8,
		0x19, 0x13, 0x4b, 0xa9, 0xd0, 0x3e, 0xfe, 0x70,
		0x25, 0x03, 0xab, 0x50, 0x6a, 0x8b, 0x82, 0x0c
	};

	rss_params->hash_secret_key_size = sizeof(rss_key);
	memcpy(rss_params->hash_secret_key, rss_key, sizeof(rss_key));
	rss_params->indirection_table_size = AQ_CFG_RSS_INDIRECTION_TABLE_MAX;

	for (i = rss_params->indirection_table_size; i--;)
		rss_params->indirection_table[i] = i & (num_rss_queues - 1);
}
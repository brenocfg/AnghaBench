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
typedef  int /*<<< orphan*/  u32 ;
struct xgene_enet_cle {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLE_CMD_WR ; 
 int /*<<< orphan*/  RSS_IPV4_HASH_SKEY ; 
 int /*<<< orphan*/  get_random_bytes (int /*<<< orphan*/ *,int) ; 
 int xgene_cle_dram_wr (struct xgene_enet_cle*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int xgene_cle_set_rss_skeys(struct xgene_enet_cle *cle)
{
	u32 secret_key_ipv4[4];  /* 16 Bytes*/
	int ret = 0;

	get_random_bytes(secret_key_ipv4, 16);
	ret = xgene_cle_dram_wr(cle, secret_key_ipv4, 4, 0,
				RSS_IPV4_HASH_SKEY, CLE_CMD_WR);
	return ret;
}
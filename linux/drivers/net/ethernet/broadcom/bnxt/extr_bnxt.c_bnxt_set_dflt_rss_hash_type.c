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
struct bnxt {int rss_hash_cfg; int hwrm_spec_code; int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 scalar_t__ BNXT_CHIP_P4 (struct bnxt*) ; 
 int /*<<< orphan*/  BNXT_FLAG_UDP_RSS_CAP ; 
 int VNIC_RSS_CFG_REQ_HASH_TYPE_IPV4 ; 
 int VNIC_RSS_CFG_REQ_HASH_TYPE_IPV6 ; 
 int VNIC_RSS_CFG_REQ_HASH_TYPE_TCP_IPV4 ; 
 int VNIC_RSS_CFG_REQ_HASH_TYPE_TCP_IPV6 ; 
 int VNIC_RSS_CFG_REQ_HASH_TYPE_UDP_IPV4 ; 
 int VNIC_RSS_CFG_REQ_HASH_TYPE_UDP_IPV6 ; 

__attribute__((used)) static void bnxt_set_dflt_rss_hash_type(struct bnxt *bp)
{
	bp->flags &= ~BNXT_FLAG_UDP_RSS_CAP;
	bp->rss_hash_cfg = VNIC_RSS_CFG_REQ_HASH_TYPE_IPV4 |
			   VNIC_RSS_CFG_REQ_HASH_TYPE_TCP_IPV4 |
			   VNIC_RSS_CFG_REQ_HASH_TYPE_IPV6 |
			   VNIC_RSS_CFG_REQ_HASH_TYPE_TCP_IPV6;
	if (BNXT_CHIP_P4(bp) && bp->hwrm_spec_code >= 0x10501) {
		bp->flags |= BNXT_FLAG_UDP_RSS_CAP;
		bp->rss_hash_cfg |= VNIC_RSS_CFG_REQ_HASH_TYPE_UDP_IPV4 |
				    VNIC_RSS_CFG_REQ_HASH_TYPE_UDP_IPV6;
	}
}
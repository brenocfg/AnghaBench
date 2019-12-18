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
struct bnxt_vnic_info {int /*<<< orphan*/  rss_hash_key; void* fw_l2_ctx_id; void** fw_rss_cos_lb_ctx; void* fw_vnic_id; } ;
struct bnxt {int nr_vnics; struct bnxt_vnic_info* vnic_info; } ;

/* Variables and functions */
 int BNXT_MAX_CTX_PER_VNIC ; 
 int /*<<< orphan*/  HW_HASH_KEY_SIZE ; 
 void* INVALID_HW_RING_ID ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  prandom_bytes (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void bnxt_init_vnics(struct bnxt *bp)
{
	int i;

	for (i = 0; i < bp->nr_vnics; i++) {
		struct bnxt_vnic_info *vnic = &bp->vnic_info[i];
		int j;

		vnic->fw_vnic_id = INVALID_HW_RING_ID;
		for (j = 0; j < BNXT_MAX_CTX_PER_VNIC; j++)
			vnic->fw_rss_cos_lb_ctx[j] = INVALID_HW_RING_ID;

		vnic->fw_l2_ctx_id = INVALID_HW_RING_ID;

		if (bp->vnic_info[i].rss_hash_key) {
			if (i == 0)
				prandom_bytes(vnic->rss_hash_key,
					      HW_HASH_KEY_SIZE);
			else
				memcpy(vnic->rss_hash_key,
				       bp->vnic_info[0].rss_hash_key,
				       HW_HASH_KEY_SIZE);
		}
	}
}
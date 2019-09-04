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
struct qed_hwfn {struct qed_cxt_mngr* p_cxt_mngr; } ;
struct qed_cxt_mngr {struct qed_cid_acquired_map** acquired_vf; struct qed_cid_acquired_map* acquired; struct qed_conn_type_cfg* conn_cfg; } ;
struct qed_conn_type_cfg {int /*<<< orphan*/  cids_per_vf; scalar_t__ cid_count; } ;
struct qed_cid_acquired_map {int /*<<< orphan*/  cid_map; int /*<<< orphan*/  max_count; } ;

/* Variables and functions */
 int BITS_PER_BYTE ; 
 int DIV_ROUND_UP (int /*<<< orphan*/ ,int) ; 
 int MAX_CONN_TYPES ; 
 size_t MAX_NUM_VFS ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t) ; 

void qed_cxt_mngr_setup(struct qed_hwfn *p_hwfn)
{
	struct qed_cxt_mngr *p_mngr = p_hwfn->p_cxt_mngr;
	struct qed_cid_acquired_map *p_map;
	struct qed_conn_type_cfg *p_cfg;
	int type;
	u32 len;

	/* Reset acquired cids */
	for (type = 0; type < MAX_CONN_TYPES; type++) {
		u32 vf;

		p_cfg = &p_mngr->conn_cfg[type];
		if (p_cfg->cid_count) {
			p_map = &p_mngr->acquired[type];
			len = DIV_ROUND_UP(p_map->max_count,
					   sizeof(unsigned long) *
					   BITS_PER_BYTE) *
			      sizeof(unsigned long);
			memset(p_map->cid_map, 0, len);
		}

		if (!p_cfg->cids_per_vf)
			continue;

		for (vf = 0; vf < MAX_NUM_VFS; vf++) {
			p_map = &p_mngr->acquired_vf[type][vf];
			len = DIV_ROUND_UP(p_map->max_count,
					   sizeof(unsigned long) *
					   BITS_PER_BYTE) *
			      sizeof(unsigned long);
			memset(p_map->cid_map, 0, len);
		}
	}
}
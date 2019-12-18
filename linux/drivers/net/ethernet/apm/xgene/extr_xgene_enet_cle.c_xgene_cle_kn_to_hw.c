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
struct xgene_cle_ptree_kn {size_t num_keys; struct xgene_cle_ptree_key* key; int /*<<< orphan*/  node_type; } ;
struct xgene_cle_ptree_key {int /*<<< orphan*/  result_pointer; int /*<<< orphan*/  priority; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLE_KN_PRIO ; 
 int /*<<< orphan*/  CLE_KN_RPTR ; 
 int /*<<< orphan*/  CLE_TYPE ; 
 size_t SET_VAL (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void xgene_cle_kn_to_hw(struct xgene_cle_ptree_kn *kn, u32 *buf)
{
	u32 i, j = 0;
	u32 data;

	buf[j++] = SET_VAL(CLE_TYPE, kn->node_type);
	for (i = 0; i < kn->num_keys; i++) {
		struct xgene_cle_ptree_key *key = &kn->key[i];

		if (!(i % 2)) {
			buf[j] = SET_VAL(CLE_KN_PRIO, key->priority) |
				 SET_VAL(CLE_KN_RPTR, key->result_pointer);
		} else {
			data = SET_VAL(CLE_KN_PRIO, key->priority) |
			       SET_VAL(CLE_KN_RPTR, key->result_pointer);
			buf[j++] |= (data << 16);
		}
	}
}
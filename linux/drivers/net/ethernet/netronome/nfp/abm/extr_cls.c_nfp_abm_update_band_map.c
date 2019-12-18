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
typedef  unsigned int u8 ;
typedef  unsigned int u32 ;
struct nfp_abm_link {int has_prio; unsigned int* prio_map; int /*<<< orphan*/  dscp_map; struct nfp_abm* abm; } ;
struct nfp_abm {unsigned int num_bands; unsigned int num_prios; } ;

/* Variables and functions */
 int BITS_PER_BYTE ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int nfp_abm_ctrl_prio_map_update (struct nfp_abm_link*,unsigned int*) ; 
 unsigned int nfp_abm_find_band_for_prio (struct nfp_abm_link*,unsigned int) ; 
 int /*<<< orphan*/  nfp_abm_qdisc_offload_update (struct nfp_abm_link*) ; 
 int order_base_2 (unsigned int) ; 
 unsigned int roundup_pow_of_two (int) ; 

__attribute__((used)) static int nfp_abm_update_band_map(struct nfp_abm_link *alink)
{
	unsigned int i, bits_per_prio, prios_per_word, base_shift;
	struct nfp_abm *abm = alink->abm;
	u32 field_mask;

	alink->has_prio = !list_empty(&alink->dscp_map);

	bits_per_prio = roundup_pow_of_two(order_base_2(abm->num_bands));
	field_mask = (1 << bits_per_prio) - 1;
	prios_per_word = sizeof(u32) * BITS_PER_BYTE / bits_per_prio;

	/* FW mask applies from top bits */
	base_shift = 8 - order_base_2(abm->num_prios);

	for (i = 0; i < abm->num_prios; i++) {
		unsigned int offset;
		u32 *word;
		u8 band;

		word = &alink->prio_map[i / prios_per_word];
		offset = (i % prios_per_word) * bits_per_prio;

		band = nfp_abm_find_band_for_prio(alink, i << base_shift);

		*word &= ~(field_mask << offset);
		*word |= band << offset;
	}

	/* Qdisc offload status may change if has_prio changed */
	nfp_abm_qdisc_offload_update(alink);

	return nfp_abm_ctrl_prio_map_update(alink, alink->prio_map);
}
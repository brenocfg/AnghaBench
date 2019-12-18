#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u8 ;
typedef  size_t u32 ;
typedef  size_t u16 ;
struct ice_xlt2 {size_t count; void* t; TYPE_2__* vsig_tbl; void* vsis; void* sid; } ;
struct ice_xlt1 {size_t count; void* t; void* ptg_tbl; void* ptypes; void* sid; } ;
struct ice_prof_tcam {size_t count; void* t; int /*<<< orphan*/  cdid_bits; int /*<<< orphan*/  max_prof_id; void* sid; } ;
struct ice_prof_redir {size_t count; void* t; void* sid; } ;
struct ice_hw {TYPE_1__* blk; } ;
struct ice_es {int count; int fvw; void* ref_count; void* written; void* t; void* sid; int /*<<< orphan*/  reverse; } ;
typedef  enum ice_status { ____Placeholder_ice_status } ice_status ;
struct TYPE_6__ {size_t xlt1; size_t xlt2; size_t prof_tcam; size_t prof_redir; int es; int fvw; int /*<<< orphan*/  prof_cdid_bits; int /*<<< orphan*/  prof_id; int /*<<< orphan*/  reverse; int /*<<< orphan*/  overwrite; } ;
struct TYPE_5__ {int /*<<< orphan*/  prop_lst; } ;
struct TYPE_4__ {int is_list_init; int /*<<< orphan*/  overwrite; struct ice_es es; struct ice_xlt2 xlt2; struct ice_xlt1 xlt1; struct ice_prof_tcam prof; struct ice_prof_redir prof_redir; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 size_t ICE_BLK_COUNT ; 
 int ICE_ERR_NO_MEMORY ; 
 size_t ICE_MAX_PTGS ; 
 size_t ICE_SID_ES_OFF ; 
 size_t ICE_SID_PR_OFF ; 
 size_t ICE_SID_PR_REDIR_OFF ; 
 size_t ICE_SID_XLT1_OFF ; 
 size_t ICE_SID_XLT2_OFF ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 TYPE_3__* blk_sizes ; 
 void* devm_kcalloc (int /*<<< orphan*/ ,size_t,int,int /*<<< orphan*/ ) ; 
 void*** ice_blk_sids ; 
 int /*<<< orphan*/  ice_free_hw_tbls (struct ice_hw*) ; 
 int /*<<< orphan*/  ice_hw_to_dev (struct ice_hw*) ; 

enum ice_status ice_init_hw_tbls(struct ice_hw *hw)
{
	u8 i;

	for (i = 0; i < ICE_BLK_COUNT; i++) {
		struct ice_prof_redir *prof_redir = &hw->blk[i].prof_redir;
		struct ice_prof_tcam *prof = &hw->blk[i].prof;
		struct ice_xlt1 *xlt1 = &hw->blk[i].xlt1;
		struct ice_xlt2 *xlt2 = &hw->blk[i].xlt2;
		struct ice_es *es = &hw->blk[i].es;
		u16 j;

		if (hw->blk[i].is_list_init)
			continue;

		hw->blk[i].is_list_init = true;

		hw->blk[i].overwrite = blk_sizes[i].overwrite;
		es->reverse = blk_sizes[i].reverse;

		xlt1->sid = ice_blk_sids[i][ICE_SID_XLT1_OFF];
		xlt1->count = blk_sizes[i].xlt1;

		xlt1->ptypes = devm_kcalloc(ice_hw_to_dev(hw), xlt1->count,
					    sizeof(*xlt1->ptypes), GFP_KERNEL);

		if (!xlt1->ptypes)
			goto err;

		xlt1->ptg_tbl = devm_kcalloc(ice_hw_to_dev(hw), ICE_MAX_PTGS,
					     sizeof(*xlt1->ptg_tbl),
					     GFP_KERNEL);

		if (!xlt1->ptg_tbl)
			goto err;

		xlt1->t = devm_kcalloc(ice_hw_to_dev(hw), xlt1->count,
				       sizeof(*xlt1->t), GFP_KERNEL);
		if (!xlt1->t)
			goto err;

		xlt2->sid = ice_blk_sids[i][ICE_SID_XLT2_OFF];
		xlt2->count = blk_sizes[i].xlt2;

		xlt2->vsis = devm_kcalloc(ice_hw_to_dev(hw), xlt2->count,
					  sizeof(*xlt2->vsis), GFP_KERNEL);

		if (!xlt2->vsis)
			goto err;

		xlt2->vsig_tbl = devm_kcalloc(ice_hw_to_dev(hw), xlt2->count,
					      sizeof(*xlt2->vsig_tbl),
					      GFP_KERNEL);
		if (!xlt2->vsig_tbl)
			goto err;

		for (j = 0; j < xlt2->count; j++)
			INIT_LIST_HEAD(&xlt2->vsig_tbl[j].prop_lst);

		xlt2->t = devm_kcalloc(ice_hw_to_dev(hw), xlt2->count,
				       sizeof(*xlt2->t), GFP_KERNEL);
		if (!xlt2->t)
			goto err;

		prof->sid = ice_blk_sids[i][ICE_SID_PR_OFF];
		prof->count = blk_sizes[i].prof_tcam;
		prof->max_prof_id = blk_sizes[i].prof_id;
		prof->cdid_bits = blk_sizes[i].prof_cdid_bits;
		prof->t = devm_kcalloc(ice_hw_to_dev(hw), prof->count,
				       sizeof(*prof->t), GFP_KERNEL);

		if (!prof->t)
			goto err;

		prof_redir->sid = ice_blk_sids[i][ICE_SID_PR_REDIR_OFF];
		prof_redir->count = blk_sizes[i].prof_redir;
		prof_redir->t = devm_kcalloc(ice_hw_to_dev(hw),
					     prof_redir->count,
					     sizeof(*prof_redir->t),
					     GFP_KERNEL);

		if (!prof_redir->t)
			goto err;

		es->sid = ice_blk_sids[i][ICE_SID_ES_OFF];
		es->count = blk_sizes[i].es;
		es->fvw = blk_sizes[i].fvw;
		es->t = devm_kcalloc(ice_hw_to_dev(hw),
				     (u32)(es->count * es->fvw),
				     sizeof(*es->t), GFP_KERNEL);
		if (!es->t)
			goto err;

		es->ref_count = devm_kcalloc(ice_hw_to_dev(hw), es->count,
					     sizeof(*es->ref_count),
					     GFP_KERNEL);

		es->written = devm_kcalloc(ice_hw_to_dev(hw), es->count,
					   sizeof(*es->written), GFP_KERNEL);
		if (!es->ref_count)
			goto err;
	}
	return 0;

err:
	ice_free_hw_tbls(hw);
	return ICE_ERR_NO_MEMORY;
}
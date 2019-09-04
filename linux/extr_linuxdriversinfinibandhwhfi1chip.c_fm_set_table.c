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
struct vl_arb_cache {int dummy; } ;
struct hfi1_pportdata {int /*<<< orphan*/  dd; } ;

/* Variables and functions */
 int EINVAL ; 
#define  FM_TBL_BUFFER_CONTROL 131 
#define  FM_TBL_SC2VLNT 130 
#define  FM_TBL_VL_HIGH_ARB 129 
#define  FM_TBL_VL_LOW_ARB 128 
 int /*<<< orphan*/  HI_PRIO_TABLE ; 
 int /*<<< orphan*/  LO_PRIO_TABLE ; 
 int /*<<< orphan*/  SEND_HIGH_PRIORITY_LIST ; 
 int /*<<< orphan*/  SEND_LOW_PRIORITY_LIST ; 
 int /*<<< orphan*/  VL_ARB_HIGH_PRIO_TABLE_SIZE ; 
 int /*<<< orphan*/  VL_ARB_LOW_PRIO_TABLE_SIZE ; 
 int set_buffer_control (struct hfi1_pportdata*,void*) ; 
 int /*<<< orphan*/  set_sc2vlnt (int /*<<< orphan*/ ,void*) ; 
 int set_vl_weights (struct hfi1_pportdata*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*) ; 
 struct vl_arb_cache* vl_arb_lock_cache (struct hfi1_pportdata*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vl_arb_match_cache (struct vl_arb_cache*,void*) ; 
 int /*<<< orphan*/  vl_arb_set_cache (struct vl_arb_cache*,void*) ; 
 int /*<<< orphan*/  vl_arb_unlock_cache (struct hfi1_pportdata*,int /*<<< orphan*/ ) ; 

int fm_set_table(struct hfi1_pportdata *ppd, int which, void *t)
{
	int ret = 0;
	struct vl_arb_cache *vlc;

	switch (which) {
	case FM_TBL_VL_HIGH_ARB:
		vlc = vl_arb_lock_cache(ppd, HI_PRIO_TABLE);
		if (vl_arb_match_cache(vlc, t)) {
			vl_arb_unlock_cache(ppd, HI_PRIO_TABLE);
			break;
		}
		vl_arb_set_cache(vlc, t);
		vl_arb_unlock_cache(ppd, HI_PRIO_TABLE);
		ret = set_vl_weights(ppd, SEND_HIGH_PRIORITY_LIST,
				     VL_ARB_HIGH_PRIO_TABLE_SIZE, t);
		break;
	case FM_TBL_VL_LOW_ARB:
		vlc = vl_arb_lock_cache(ppd, LO_PRIO_TABLE);
		if (vl_arb_match_cache(vlc, t)) {
			vl_arb_unlock_cache(ppd, LO_PRIO_TABLE);
			break;
		}
		vl_arb_set_cache(vlc, t);
		vl_arb_unlock_cache(ppd, LO_PRIO_TABLE);
		ret = set_vl_weights(ppd, SEND_LOW_PRIORITY_LIST,
				     VL_ARB_LOW_PRIO_TABLE_SIZE, t);
		break;
	case FM_TBL_BUFFER_CONTROL:
		ret = set_buffer_control(ppd, t);
		break;
	case FM_TBL_SC2VLNT:
		set_sc2vlnt(ppd->dd, t);
		break;
	default:
		ret = -EINVAL;
	}
	return ret;
}
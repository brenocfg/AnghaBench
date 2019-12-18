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
typedef  scalar_t__ u8 ;
typedef  int u64 ;
typedef  int u32 ;
struct qed_ptt {int dummy; } ;
struct qed_llh_filter_details {int enable; int value; int mode; scalar_t__ protocol_type; scalar_t__ hdr_sel; } ;
struct qed_hwfn {int dummy; } ;

/* Variables and functions */
 int qed_llh_access_filter (struct qed_hwfn*,struct qed_ptt*,scalar_t__,scalar_t__,struct qed_llh_filter_details*) ; 

__attribute__((used)) static int
qed_llh_add_filter(struct qed_hwfn *p_hwfn,
		   struct qed_ptt *p_ptt,
		   u8 abs_ppfid,
		   u8 filter_idx, u8 filter_prot_type, u32 high, u32 low)
{
	struct qed_llh_filter_details filter_details;

	filter_details.enable = 1;
	filter_details.value = ((u64)high << 32) | low;
	filter_details.hdr_sel = 0;
	filter_details.protocol_type = filter_prot_type;
	/* Mode: 0: MAC-address classification 1: protocol classification */
	filter_details.mode = filter_prot_type ? 1 : 0;

	return qed_llh_access_filter(p_hwfn, p_ptt, abs_ppfid, filter_idx,
				     &filter_details);
}
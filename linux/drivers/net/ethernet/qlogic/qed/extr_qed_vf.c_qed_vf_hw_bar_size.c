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
typedef  int u32 ;
struct qed_hwfn {TYPE_3__* vf_iov_info; } ;
typedef  enum BAR_ID { ____Placeholder_BAR_ID } BAR_ID ;
struct TYPE_4__ {int bar_size; } ;
struct TYPE_5__ {TYPE_1__ pfdev_info; } ;
struct TYPE_6__ {TYPE_2__ acquire_resp; } ;

/* Variables and functions */
 int BAR_ID_0 ; 

u32 qed_vf_hw_bar_size(struct qed_hwfn *p_hwfn, enum BAR_ID bar_id)
{
	u32 bar_size;

	/* Regview size is fixed */
	if (bar_id == BAR_ID_0)
		return 1 << 17;

	/* Doorbell is received from PF */
	bar_size = p_hwfn->vf_iov_info->acquire_resp.pfdev_info.bar_size;
	if (bar_size)
		return 1 << bar_size;
	return 0;
}
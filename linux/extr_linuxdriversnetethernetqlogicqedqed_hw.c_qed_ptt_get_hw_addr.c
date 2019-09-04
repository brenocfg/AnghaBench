#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_2__ {int /*<<< orphan*/  offset; } ;
struct qed_ptt {TYPE_1__ pxp; } ;
struct qed_hwfn {int dummy; } ;

/* Variables and functions */
 int le32_to_cpu (int /*<<< orphan*/ ) ; 

u32 qed_ptt_get_hw_addr(struct qed_hwfn *p_hwfn, struct qed_ptt *p_ptt)
{
	/* The HW is using DWORDS and we need to translate it to Bytes */
	return le32_to_cpu(p_ptt->pxp.offset) << 2;
}
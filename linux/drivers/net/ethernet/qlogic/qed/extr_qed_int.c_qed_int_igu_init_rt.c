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
typedef  int /*<<< orphan*/  u32 ;
struct qed_hwfn {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IGU_PF_CONF_FUNC_EN ; 
 int /*<<< orphan*/  IGU_REG_PF_CONFIGURATION_RT_OFFSET ; 
 int /*<<< orphan*/  STORE_RT_REG (struct qed_hwfn*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void qed_int_igu_init_rt(struct qed_hwfn *p_hwfn)
{
	u32 igu_pf_conf = IGU_PF_CONF_FUNC_EN;

	STORE_RT_REG(p_hwfn, IGU_REG_PF_CONFIGURATION_RT_OFFSET, igu_pf_conf);
}
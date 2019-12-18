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
struct mpc {int dummy; } ;
struct dcn20_mpc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/ * MPCC_MEM_PWR_CTRL ; 
 int /*<<< orphan*/  MPCC_OGAM_MEM_PWR_DIS ; 
 int /*<<< orphan*/  REG_SET (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct dcn20_mpc* TO_DCN20_MPC (struct mpc*) ; 

void mpc20_power_on_ogam_lut(
		struct mpc *mpc, int mpcc_id,
		bool power_on)
{
	struct dcn20_mpc *mpc20 = TO_DCN20_MPC(mpc);

	REG_SET(MPCC_MEM_PWR_CTRL[mpcc_id], 0,
			MPCC_OGAM_MEM_PWR_DIS, power_on == true ? 1:0);

}
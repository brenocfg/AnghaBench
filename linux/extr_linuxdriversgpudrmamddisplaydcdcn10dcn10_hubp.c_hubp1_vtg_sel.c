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
typedef  int /*<<< orphan*/  uint32_t ;
struct hubp {int dummy; } ;
struct dcn10_hubp {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DCHUBP_CNTL ; 
 int /*<<< orphan*/  HUBP_VTG_SEL ; 
 int /*<<< orphan*/  REG_UPDATE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct dcn10_hubp* TO_DCN10_HUBP (struct hubp*) ; 

void hubp1_vtg_sel(struct hubp *hubp, uint32_t otg_inst)
{
	struct dcn10_hubp *hubp1 = TO_DCN10_HUBP(hubp);

	REG_UPDATE(DCHUBP_CNTL, HUBP_VTG_SEL, otg_inst);
}
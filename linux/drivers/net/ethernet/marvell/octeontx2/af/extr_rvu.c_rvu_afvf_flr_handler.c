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
struct rvu {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT_ULL (int) ; 
 int /*<<< orphan*/  RVU_PF_VFFLR_INT_ENA_W1SX (int) ; 
 int /*<<< orphan*/  RVU_PF_VFTRPENDX (int) ; 
 int /*<<< orphan*/  __rvu_flr_handler (struct rvu*,int) ; 
 int /*<<< orphan*/  rvupf_write64 (struct rvu*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void rvu_afvf_flr_handler(struct rvu *rvu, int vf)
{
	int reg = 0;

	/* pcifunc = 0(PF0) | (vf + 1) */
	__rvu_flr_handler(rvu, vf + 1);

	if (vf >= 64) {
		reg = 1;
		vf = vf - 64;
	}

	/* Signal FLR finish and enable IRQ */
	rvupf_write64(rvu, RVU_PF_VFTRPENDX(reg), BIT_ULL(vf));
	rvupf_write64(rvu, RVU_PF_VFFLR_INT_ENA_W1SX(reg), BIT_ULL(vf));
}
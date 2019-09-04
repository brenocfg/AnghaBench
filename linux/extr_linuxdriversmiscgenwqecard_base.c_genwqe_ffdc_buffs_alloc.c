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
struct genwqe_reg {int dummy; } ;
struct genwqe_dev {TYPE_1__* ffdc; } ;
struct TYPE_2__ {unsigned int entries; int /*<<< orphan*/  regs; } ;

/* Variables and functions */
#define  GENWQE_DBG_REGS 131 
#define  GENWQE_DBG_UNIT0 130 
#define  GENWQE_DBG_UNIT1 129 
#define  GENWQE_DBG_UNIT2 128 
 unsigned int GENWQE_DBG_UNITS ; 
 unsigned int GENWQE_FFDC_REGS ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 unsigned int genwqe_ffdc_buff_size (struct genwqe_dev*,int) ; 
 int /*<<< orphan*/  kmalloc_array (unsigned int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int genwqe_ffdc_buffs_alloc(struct genwqe_dev *cd)
{
	unsigned int type, e = 0;

	for (type = 0; type < GENWQE_DBG_UNITS; type++) {
		switch (type) {
		case GENWQE_DBG_UNIT0:
			e = genwqe_ffdc_buff_size(cd, 0);
			break;
		case GENWQE_DBG_UNIT1:
			e = genwqe_ffdc_buff_size(cd, 1);
			break;
		case GENWQE_DBG_UNIT2:
			e = genwqe_ffdc_buff_size(cd, 2);
			break;
		case GENWQE_DBG_REGS:
			e = GENWQE_FFDC_REGS;
			break;
		}

		/* currently support only the debug units mentioned here */
		cd->ffdc[type].entries = e;
		cd->ffdc[type].regs =
			kmalloc_array(e, sizeof(struct genwqe_reg),
				      GFP_KERNEL);
		/*
		 * regs == NULL is ok, the using code treats this as no regs,
		 * Printing warning is ok in this case.
		 */
	}
	return 0;
}
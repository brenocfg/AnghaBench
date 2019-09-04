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
struct hubdev_info {int /*<<< orphan*/  hdi_nasid; } ;
struct TYPE_2__ {int ii_icrb0_b_regval; scalar_t__ b_mark; } ;
typedef  TYPE_1__ ii_icrb0_b_u_t ;

/* Variables and functions */
 int /*<<< orphan*/  IIO_ICDR ; 
 int IIO_ICDR_PND ; 
 int /*<<< orphan*/  IIO_ICRB_B (int) ; 
 int REMOTE_HUB_L (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REMOTE_HUB_S (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  cpu_relax () ; 

void hubiio_crb_free(struct hubdev_info *hubdev_info, int crbnum)
{
	ii_icrb0_b_u_t icrbb;

	/*
	 * The hardware does NOT clear the mark bit, so it must get cleared
	 * here to be sure the error is not processed twice.
	 */
	icrbb.ii_icrb0_b_regval = REMOTE_HUB_L(hubdev_info->hdi_nasid,
					       IIO_ICRB_B(crbnum));
	icrbb.b_mark = 0;
	REMOTE_HUB_S(hubdev_info->hdi_nasid, IIO_ICRB_B(crbnum),
		     icrbb.ii_icrb0_b_regval);
	/*
	 * Deallocate the register wait till hub indicates it's done.
	 */
	REMOTE_HUB_S(hubdev_info->hdi_nasid, IIO_ICDR, (IIO_ICDR_PND | crbnum));
	while (REMOTE_HUB_L(hubdev_info->hdi_nasid, IIO_ICDR) & IIO_ICDR_PND)
		cpu_relax();

}
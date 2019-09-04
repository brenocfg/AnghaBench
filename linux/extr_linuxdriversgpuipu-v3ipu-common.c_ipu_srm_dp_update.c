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
struct ipu_soc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DP_S_SRM_MODE_MASK ; 
 int /*<<< orphan*/  DP_S_SRM_MODE_NEXT_FRAME ; 
 int /*<<< orphan*/  DP_S_SRM_MODE_NOW ; 
 int /*<<< orphan*/  IPU_SRM_PRI2 ; 
 int /*<<< orphan*/  ipu_cm_read (struct ipu_soc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipu_cm_write (struct ipu_soc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void ipu_srm_dp_update(struct ipu_soc *ipu, bool sync)
{
	u32 val;

	val = ipu_cm_read(ipu, IPU_SRM_PRI2);
	val &= ~DP_S_SRM_MODE_MASK;
	val |= sync ? DP_S_SRM_MODE_NEXT_FRAME :
		      DP_S_SRM_MODE_NOW;
	ipu_cm_write(ipu, val, IPU_SRM_PRI2);
}
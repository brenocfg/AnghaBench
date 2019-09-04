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
struct dpu_hw_ctl {int dummy; } ;
typedef  enum dpu_cdm { ____Placeholder_dpu_cdm } dpu_cdm ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (int) ; 
#define  CDM_0 128 
 int EINVAL ; 

__attribute__((used)) static inline int dpu_hw_ctl_get_bitmask_cdm(struct dpu_hw_ctl *ctx,
		u32 *flushbits, enum dpu_cdm cdm)
{
	switch (cdm) {
	case CDM_0:
		*flushbits |= BIT(26);
		break;
	default:
		return -EINVAL;
	}
	return 0;
}
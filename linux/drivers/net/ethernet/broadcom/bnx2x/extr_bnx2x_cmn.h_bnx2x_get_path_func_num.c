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
typedef  int u8 ;
typedef  int u32 ;
struct bnx2x {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  config; } ;

/* Variables and functions */
 int BP_PORT (struct bnx2x*) ; 
 scalar_t__ CHIP_IS_E1 (struct bnx2x*) ; 
 scalar_t__ CHIP_REV_IS_SLOW (struct bnx2x*) ; 
 int E1H_FUNC_MAX ; 
 int FUNC_MF_CFG_FUNC_HIDE ; 
 scalar_t__ IS_MF (struct bnx2x*) ; 
 int MF_CFG_RD (struct bnx2x*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 TYPE_1__* func_mf_config ; 

__attribute__((used)) static inline u8 bnx2x_get_path_func_num(struct bnx2x *bp)
{
	u8 func_num = 0, i;

	/* 57710 has only one function per-port */
	if (CHIP_IS_E1(bp))
		return 1;

	/* Calculate a number of functions enabled on the current
	 * PATH/PORT.
	 */
	if (CHIP_REV_IS_SLOW(bp)) {
		if (IS_MF(bp))
			func_num = 4;
		else
			func_num = 2;
	} else {
		for (i = 0; i < E1H_FUNC_MAX / 2; i++) {
			u32 func_config =
				MF_CFG_RD(bp,
					  func_mf_config[BP_PORT(bp) + 2 * i].
					  config);
			func_num +=
				((func_config & FUNC_MF_CFG_FUNC_HIDE) ? 0 : 1);
		}
	}

	WARN_ON(!func_num);

	return func_num;
}
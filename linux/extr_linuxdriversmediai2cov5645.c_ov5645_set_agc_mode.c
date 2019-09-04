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
typedef  int /*<<< orphan*/  u8 ;
typedef  scalar_t__ u32 ;
struct ov5645 {int /*<<< orphan*/  aec_pk_manual; } ;

/* Variables and functions */
 int /*<<< orphan*/  OV5645_AEC_PK_MANUAL ; 
 int /*<<< orphan*/  OV5645_AGC_MANUAL_ENABLE ; 
 int ov5645_write_reg (struct ov5645*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ov5645_set_agc_mode(struct ov5645 *ov5645, u32 enable)
{
	u8 val = ov5645->aec_pk_manual;
	int ret;

	if (enable)
		val &= ~OV5645_AGC_MANUAL_ENABLE;
	else
		val |= OV5645_AGC_MANUAL_ENABLE;

	ret = ov5645_write_reg(ov5645, OV5645_AEC_PK_MANUAL, val);
	if (!ret)
		ov5645->aec_pk_manual = val;

	return ret;
}
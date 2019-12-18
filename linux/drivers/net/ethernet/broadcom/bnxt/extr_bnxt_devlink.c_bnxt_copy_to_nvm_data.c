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
union devlink_param_value {scalar_t__ vu8; scalar_t__ vu16; scalar_t__ vu32; int /*<<< orphan*/  vbool; } ;
union bnxt_nvm_data {int /*<<< orphan*/  val32; int /*<<< orphan*/  val8; } ;
typedef  scalar_t__ u32 ;

/* Variables and functions */
 int /*<<< orphan*/  cpu_to_le32 (scalar_t__) ; 

__attribute__((used)) static void bnxt_copy_to_nvm_data(union bnxt_nvm_data *dst,
				  union devlink_param_value *src,
				  int nvm_num_bits, int dl_num_bytes)
{
	u32 val32 = 0;

	if (nvm_num_bits == 1) {
		dst->val8 = src->vbool;
		return;
	}
	if (dl_num_bytes == 4)
		val32 = src->vu32;
	else if (dl_num_bytes == 2)
		val32 = (u32)src->vu16;
	else if (dl_num_bytes == 1)
		val32 = (u32)src->vu8;
	dst->val32 = cpu_to_le32(val32);
}
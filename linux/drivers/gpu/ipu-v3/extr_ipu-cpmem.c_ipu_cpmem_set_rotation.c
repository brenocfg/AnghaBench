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
typedef  int u32 ;
struct ipuv3_channel {int dummy; } ;
typedef  enum ipu_rotate_mode { ____Placeholder_ipu_rotate_mode } ipu_rotate_mode ;

/* Variables and functions */
 int /*<<< orphan*/  IPU_FIELD_ROT_HF_VF ; 
 int bitrev8 (int) ; 
 int /*<<< orphan*/  ipu_ch_param_write_field (struct ipuv3_channel*,int /*<<< orphan*/ ,int) ; 

void ipu_cpmem_set_rotation(struct ipuv3_channel *ch,
			    enum ipu_rotate_mode rot)
{
	u32 temp_rot = bitrev8(rot) >> 5;

	ipu_ch_param_write_field(ch, IPU_FIELD_ROT_HF_VF, temp_rot);
}
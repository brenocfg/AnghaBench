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
struct ipuv3_channel {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IPU_FIELD_SLUV ; 
 int /*<<< orphan*/  IPU_FIELD_UBO ; 
 int /*<<< orphan*/  IPU_FIELD_VBO ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  ipu_ch_param_write_field (struct ipuv3_channel*,int /*<<< orphan*/ ,unsigned int) ; 

void ipu_cpmem_set_yuv_planar_full(struct ipuv3_channel *ch,
				   unsigned int uv_stride,
				   unsigned int u_offset, unsigned int v_offset)
{
	WARN_ON_ONCE((u_offset & 0x7) || (v_offset & 0x7));

	ipu_ch_param_write_field(ch, IPU_FIELD_SLUV, uv_stride - 1);
	ipu_ch_param_write_field(ch, IPU_FIELD_UBO, u_offset / 8);
	ipu_ch_param_write_field(ch, IPU_FIELD_VBO, v_offset / 8);
}
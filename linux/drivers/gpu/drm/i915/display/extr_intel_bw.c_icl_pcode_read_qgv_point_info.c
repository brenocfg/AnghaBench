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
struct intel_qgv_point {int dclk; int t_rp; int t_rcd; int t_rdpre; int t_ras; int t_rc; } ;
struct drm_i915_private {int dummy; } ;

/* Variables and functions */
 int ICL_PCODE_MEM_SS_READ_QGV_POINT_INFO (int) ; 
 int ICL_PCODE_MEM_SUBSYSYSTEM_INFO ; 
 int sandybridge_pcode_read (struct drm_i915_private*,int,int*,int*) ; 

__attribute__((used)) static int icl_pcode_read_qgv_point_info(struct drm_i915_private *dev_priv,
					 struct intel_qgv_point *sp,
					 int point)
{
	u32 val = 0, val2 = 0;
	int ret;

	ret = sandybridge_pcode_read(dev_priv,
				     ICL_PCODE_MEM_SUBSYSYSTEM_INFO |
				     ICL_PCODE_MEM_SS_READ_QGV_POINT_INFO(point),
				     &val, &val2);
	if (ret)
		return ret;

	sp->dclk = val & 0xffff;
	sp->t_rp = (val & 0xff0000) >> 16;
	sp->t_rcd = (val & 0xff000000) >> 24;

	sp->t_rdpre = val2 & 0xff;
	sp->t_ras = (val2 & 0xff00) >> 8;

	sp->t_rc = sp->t_rp + sp->t_ras;

	return 0;
}
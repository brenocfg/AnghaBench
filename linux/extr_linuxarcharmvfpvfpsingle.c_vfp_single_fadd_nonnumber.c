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
struct vfp_single {int sign; } ;

/* Variables and functions */
 int /*<<< orphan*/  FPSCR_IOC ; 
 int VFP_INFINITY ; 
 int VFP_NUMBER ; 
 int /*<<< orphan*/  vfp_propagate_nan (struct vfp_single*,struct vfp_single*,struct vfp_single*,int /*<<< orphan*/ ) ; 
 struct vfp_single vfp_single_default_qnan ; 
 int vfp_single_type (struct vfp_single*) ; 

__attribute__((used)) static u32
vfp_single_fadd_nonnumber(struct vfp_single *vsd, struct vfp_single *vsn,
			  struct vfp_single *vsm, u32 fpscr)
{
	struct vfp_single *vsp;
	u32 exceptions = 0;
	int tn, tm;

	tn = vfp_single_type(vsn);
	tm = vfp_single_type(vsm);

	if (tn & tm & VFP_INFINITY) {
		/*
		 * Two infinities.  Are they different signs?
		 */
		if (vsn->sign ^ vsm->sign) {
			/*
			 * different signs -> invalid
			 */
			exceptions = FPSCR_IOC;
			vsp = &vfp_single_default_qnan;
		} else {
			/*
			 * same signs -> valid
			 */
			vsp = vsn;
		}
	} else if (tn & VFP_INFINITY && tm & VFP_NUMBER) {
		/*
		 * One infinity and one number -> infinity
		 */
		vsp = vsn;
	} else {
		/*
		 * 'n' is a NaN of some type
		 */
		return vfp_propagate_nan(vsd, vsn, vsm, fpscr);
	}
	*vsd = *vsp;
	return exceptions;
}
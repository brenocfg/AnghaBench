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
struct TYPE_2__ {int dovf; } ;
union cptx_vqx_misc_int {int /*<<< orphan*/  u; TYPE_1__ s; } ;
struct cpt_vf {int /*<<< orphan*/  reg_base; } ;

/* Variables and functions */
 int /*<<< orphan*/  CPTX_VQX_MISC_INT (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpt_read_csr64 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpt_write_csr64 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void cptvf_clear_dovf_intr(struct cpt_vf *cptvf)
{
	union cptx_vqx_misc_int vqx_misc_int;

	vqx_misc_int.u = cpt_read_csr64(cptvf->reg_base,
					CPTX_VQX_MISC_INT(0, 0));
	/* W1C for the VF */
	vqx_misc_int.s.dovf = 1;
	cpt_write_csr64(cptvf->reg_base, CPTX_VQX_MISC_INT(0, 0),
			vqx_misc_int.u);
}
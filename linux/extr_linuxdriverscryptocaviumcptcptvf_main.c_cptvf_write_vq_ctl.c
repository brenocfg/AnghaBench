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
struct TYPE_2__ {int ena; } ;
union cptx_vqx_ctl {int /*<<< orphan*/  u; TYPE_1__ s; } ;
struct cpt_vf {int /*<<< orphan*/  reg_base; } ;

/* Variables and functions */
 int /*<<< orphan*/  CPTX_VQX_CTL (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpt_read_csr64 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpt_write_csr64 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void cptvf_write_vq_ctl(struct cpt_vf *cptvf, bool val)
{
	union cptx_vqx_ctl vqx_ctl;

	vqx_ctl.u = cpt_read_csr64(cptvf->reg_base, CPTX_VQX_CTL(0, 0));
	vqx_ctl.s.ena = val;
	cpt_write_csr64(cptvf->reg_base, CPTX_VQX_CTL(0, 0), vqx_ctl.u);
}
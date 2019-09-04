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
struct cpt_vf {int /*<<< orphan*/  reg_base; } ;
struct cpt_mbox {int /*<<< orphan*/  data; int /*<<< orphan*/  msg; } ;

/* Variables and functions */
 int /*<<< orphan*/  CPTX_VFX_PF_MBOXX (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  cpt_write_csr64 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void cptvf_send_msg_to_pf(struct cpt_vf *cptvf, struct cpt_mbox *mbx)
{
	/* Writing mbox(1) causes interrupt */
	cpt_write_csr64(cptvf->reg_base, CPTX_VFX_PF_MBOXX(0, 0, 0),
			mbx->msg);
	cpt_write_csr64(cptvf->reg_base, CPTX_VFX_PF_MBOXX(0, 0, 1),
			mbx->data);
}
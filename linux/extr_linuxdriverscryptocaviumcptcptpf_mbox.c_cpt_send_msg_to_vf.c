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
struct cpt_mbox {int /*<<< orphan*/  msg; int /*<<< orphan*/  data; } ;
struct cpt_device {int /*<<< orphan*/  reg_base; } ;

/* Variables and functions */
 int /*<<< orphan*/  CPTX_PF_VFX_MBOXX (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  cpt_write_csr64 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void cpt_send_msg_to_vf(struct cpt_device *cpt, int vf,
			       struct cpt_mbox *mbx)
{
	/* Writing mbox(0) causes interrupt */
	cpt_write_csr64(cpt->reg_base, CPTX_PF_VFX_MBOXX(0, vf, 1),
			mbx->data);
	cpt_write_csr64(cpt->reg_base, CPTX_PF_VFX_MBOXX(0, vf, 0), mbx->msg);
}
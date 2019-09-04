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
struct TYPE_2__ {int dbell_cnt; } ;
union cptx_vqx_doorbell {int /*<<< orphan*/  u; TYPE_1__ s; } ;
typedef  int u32 ;
struct cpt_vf {int /*<<< orphan*/  reg_base; } ;

/* Variables and functions */
 int /*<<< orphan*/  CPTX_VQX_DOORBELL (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpt_read_csr64 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpt_write_csr64 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void cptvf_write_vq_doorbell(struct cpt_vf *cptvf, u32 val)
{
	union cptx_vqx_doorbell vqx_dbell;

	vqx_dbell.u = cpt_read_csr64(cptvf->reg_base,
				     CPTX_VQX_DOORBELL(0, 0));
	vqx_dbell.s.dbell_cnt = val * 8; /* Num of Instructions * 8 words */
	cpt_write_csr64(cptvf->reg_base, CPTX_VQX_DOORBELL(0, 0),
			vqx_dbell.u);
}
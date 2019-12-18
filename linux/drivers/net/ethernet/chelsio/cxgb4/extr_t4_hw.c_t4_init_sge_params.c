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
typedef  unsigned int u32 ;
struct sge_params {unsigned int hps; unsigned int eq_qpp; unsigned int iq_qpp; } ;
struct TYPE_2__ {struct sge_params sge; } ;
struct adapter {unsigned int pf; TYPE_1__ params; } ;

/* Variables and functions */
 unsigned int HOSTPAGESIZEPF0_M ; 
 unsigned int HOSTPAGESIZEPF0_S ; 
 unsigned int HOSTPAGESIZEPF1_S ; 
 unsigned int QUEUESPERPAGEPF0_M ; 
 unsigned int QUEUESPERPAGEPF0_S ; 
 unsigned int QUEUESPERPAGEPF1_S ; 
 int /*<<< orphan*/  SGE_EGRESS_QUEUES_PER_PAGE_PF_A ; 
 int /*<<< orphan*/  SGE_HOST_PAGE_SIZE_A ; 
 int /*<<< orphan*/  SGE_INGRESS_QUEUES_PER_PAGE_PF_A ; 
 unsigned int t4_read_reg (struct adapter*,int /*<<< orphan*/ ) ; 

int t4_init_sge_params(struct adapter *adapter)
{
	struct sge_params *sge_params = &adapter->params.sge;
	u32 hps, qpp;
	unsigned int s_hps, s_qpp;

	/* Extract the SGE Page Size for our PF.
	 */
	hps = t4_read_reg(adapter, SGE_HOST_PAGE_SIZE_A);
	s_hps = (HOSTPAGESIZEPF0_S +
		 (HOSTPAGESIZEPF1_S - HOSTPAGESIZEPF0_S) * adapter->pf);
	sge_params->hps = ((hps >> s_hps) & HOSTPAGESIZEPF0_M);

	/* Extract the SGE Egress and Ingess Queues Per Page for our PF.
	 */
	s_qpp = (QUEUESPERPAGEPF0_S +
		(QUEUESPERPAGEPF1_S - QUEUESPERPAGEPF0_S) * adapter->pf);
	qpp = t4_read_reg(adapter, SGE_EGRESS_QUEUES_PER_PAGE_PF_A);
	sge_params->eq_qpp = ((qpp >> s_qpp) & QUEUESPERPAGEPF0_M);
	qpp = t4_read_reg(adapter, SGE_INGRESS_QUEUES_PER_PAGE_PF_A);
	sge_params->iq_qpp = ((qpp >> s_qpp) & QUEUESPERPAGEPF0_M);

	return 0;
}
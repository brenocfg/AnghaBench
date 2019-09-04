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
struct cptvf_wqe_info {struct cptvf_wqe* vq_wqe; } ;
struct cptvf_wqe {int dummy; } ;
struct cpt_vf {int nr_queues; scalar_t__ wqe_info; } ;

/* Variables and functions */
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static inline struct cptvf_wqe *get_cptvf_vq_wqe(struct cpt_vf *cptvf,
						 int qno)
{
	struct cptvf_wqe_info *nwqe_info;

	if (unlikely(qno >= cptvf->nr_queues))
		return NULL;
	nwqe_info = (struct cptvf_wqe_info *)cptvf->wqe_info;

	return &nwqe_info->vq_wqe[qno];
}
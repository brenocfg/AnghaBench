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
typedef  size_t u32 ;
struct etnaviv_pm_signal {size_t (* sample ) (struct etnaviv_gpu*,struct etnaviv_pm_domain const*,struct etnaviv_pm_signal const*) ;} ;
struct etnaviv_pm_domain_meta {struct etnaviv_pm_domain* domains; } ;
struct etnaviv_pm_domain {struct etnaviv_pm_signal* signal; } ;
struct etnaviv_perfmon_request {size_t* bo_vma; int domain; size_t signal; int offset; } ;
struct etnaviv_gpu {int dummy; } ;

/* Variables and functions */
 struct etnaviv_pm_domain_meta* doms_meta ; 
 size_t stub1 (struct etnaviv_gpu*,struct etnaviv_pm_domain const*,struct etnaviv_pm_signal const*) ; 

void etnaviv_perfmon_process(struct etnaviv_gpu *gpu,
	const struct etnaviv_perfmon_request *pmr, u32 exec_state)
{
	const struct etnaviv_pm_domain_meta *meta = &doms_meta[exec_state];
	const struct etnaviv_pm_domain *dom;
	const struct etnaviv_pm_signal *sig;
	u32 *bo = pmr->bo_vma;
	u32 val;

	dom = meta->domains + pmr->domain;
	sig = &dom->signal[pmr->signal];
	val = sig->sample(gpu, dom, sig);

	*(bo + pmr->offset) = val;
}
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
struct rvu_pfvf {int dummy; } ;
struct rvu {struct rvu_pfvf* pf; struct rvu_pfvf* hwvf; } ;

/* Variables and functions */
 int RVU_PFVF_FUNC_MASK ; 
 size_t rvu_get_hwvf (struct rvu*,int) ; 
 size_t rvu_get_pf (int) ; 

struct rvu_pfvf *rvu_get_pfvf(struct rvu *rvu, int pcifunc)
{
	/* Check if it is a PF or VF */
	if (pcifunc & RVU_PFVF_FUNC_MASK)
		return &rvu->hwvf[rvu_get_hwvf(rvu, pcifunc)];
	else
		return &rvu->pf[rvu_get_pf(pcifunc)];
}
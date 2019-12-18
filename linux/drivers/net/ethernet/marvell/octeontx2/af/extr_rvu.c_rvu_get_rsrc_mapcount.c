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
typedef  int u16 ;
struct rvu_pfvf {int sso; int ssow; int timlfs; int cptlfs; int /*<<< orphan*/  nixlf; int /*<<< orphan*/  npalf; } ;

/* Variables and functions */
#define  BLKTYPE_CPT 133 
#define  BLKTYPE_NIX 132 
#define  BLKTYPE_NPA 131 
#define  BLKTYPE_SSO 130 
#define  BLKTYPE_SSOW 129 
#define  BLKTYPE_TIM 128 

__attribute__((used)) static u16 rvu_get_rsrc_mapcount(struct rvu_pfvf *pfvf, int blktype)
{
	switch (blktype) {
	case BLKTYPE_NPA:
		return pfvf->npalf ? 1 : 0;
	case BLKTYPE_NIX:
		return pfvf->nixlf ? 1 : 0;
	case BLKTYPE_SSO:
		return pfvf->sso;
	case BLKTYPE_SSOW:
		return pfvf->ssow;
	case BLKTYPE_TIM:
		return pfvf->timlfs;
	case BLKTYPE_CPT:
		return pfvf->cptlfs;
	}
	return 0;
}
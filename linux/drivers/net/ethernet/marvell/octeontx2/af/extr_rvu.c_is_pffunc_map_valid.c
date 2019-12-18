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
typedef  int /*<<< orphan*/  u16 ;
struct rvu_pfvf {int dummy; } ;
struct rvu {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  is_pf_func_valid (struct rvu*,int /*<<< orphan*/ ) ; 
 struct rvu_pfvf* rvu_get_pfvf (struct rvu*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rvu_get_rsrc_mapcount (struct rvu_pfvf*,int) ; 

bool is_pffunc_map_valid(struct rvu *rvu, u16 pcifunc, int blktype)
{
	struct rvu_pfvf *pfvf;

	if (!is_pf_func_valid(rvu, pcifunc))
		return false;

	pfvf = rvu_get_pfvf(rvu, pcifunc);

	/* Check if this PFFUNC has a LF of type blktype attached */
	if (!rvu_get_rsrc_mapcount(pfvf, blktype))
		return false;

	return true;
}
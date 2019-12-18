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
struct rvu {int /*<<< orphan*/  flr_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  BLKADDR_CPT0 ; 
 int /*<<< orphan*/  BLKADDR_NIX0 ; 
 int /*<<< orphan*/  BLKADDR_NPA ; 
 int /*<<< orphan*/  BLKADDR_SSO ; 
 int /*<<< orphan*/  BLKADDR_SSOW ; 
 int /*<<< orphan*/  BLKADDR_TIM ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rvu_blklf_teardown (struct rvu*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rvu_detach_rsrcs (struct rvu*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void __rvu_flr_handler(struct rvu *rvu, u16 pcifunc)
{
	mutex_lock(&rvu->flr_lock);
	/* Reset order should reflect inter-block dependencies:
	 * 1. Reset any packet/work sources (NIX, CPT, TIM)
	 * 2. Flush and reset SSO/SSOW
	 * 3. Cleanup pools (NPA)
	 */
	rvu_blklf_teardown(rvu, pcifunc, BLKADDR_NIX0);
	rvu_blklf_teardown(rvu, pcifunc, BLKADDR_CPT0);
	rvu_blklf_teardown(rvu, pcifunc, BLKADDR_TIM);
	rvu_blklf_teardown(rvu, pcifunc, BLKADDR_SSOW);
	rvu_blklf_teardown(rvu, pcifunc, BLKADDR_SSO);
	rvu_blklf_teardown(rvu, pcifunc, BLKADDR_NPA);
	rvu_detach_rsrcs(rvu, NULL, pcifunc);
	mutex_unlock(&rvu->flr_lock);
}
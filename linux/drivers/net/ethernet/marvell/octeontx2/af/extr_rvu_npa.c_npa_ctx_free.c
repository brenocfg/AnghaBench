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
struct rvu_pfvf {int /*<<< orphan*/ * npa_qints_ctx; int /*<<< orphan*/ * pool_ctx; int /*<<< orphan*/ * pool_bmap; int /*<<< orphan*/ * aura_ctx; int /*<<< orphan*/ * aura_bmap; } ;
struct rvu {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  qmem_free (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void npa_ctx_free(struct rvu *rvu, struct rvu_pfvf *pfvf)
{
	kfree(pfvf->aura_bmap);
	pfvf->aura_bmap = NULL;

	qmem_free(rvu->dev, pfvf->aura_ctx);
	pfvf->aura_ctx = NULL;

	kfree(pfvf->pool_bmap);
	pfvf->pool_bmap = NULL;

	qmem_free(rvu->dev, pfvf->pool_ctx);
	pfvf->pool_ctx = NULL;

	qmem_free(rvu->dev, pfvf->npa_qints_ctx);
	pfvf->npa_qints_ctx = NULL;
}
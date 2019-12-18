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
struct whc_qset {int /*<<< orphan*/  qset_dma; } ;
struct whc {int /*<<< orphan*/  qset_pool; } ;

/* Variables and functions */
 int /*<<< orphan*/  dma_pool_free (int /*<<< orphan*/ ,struct whc_qset*,int /*<<< orphan*/ ) ; 

void qset_free(struct whc *whc, struct whc_qset *qset)
{
	dma_pool_free(whc->qset_pool, qset, qset->qset_dma);
}
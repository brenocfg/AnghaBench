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
struct he_tpd {TYPE_1__* iovec; scalar_t__ reserved; int /*<<< orphan*/  status; } ;
struct he_dev {int /*<<< orphan*/  tpd_pool; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;
struct TYPE_2__ {scalar_t__ len; scalar_t__ addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  TPD_ADDR (int /*<<< orphan*/ ) ; 
 struct he_tpd* dma_pool_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct he_tpd *
__alloc_tpd(struct he_dev *he_dev)
{
	struct he_tpd *tpd;
	dma_addr_t mapping;

	tpd = dma_pool_alloc(he_dev->tpd_pool, GFP_ATOMIC, &mapping);
	if (tpd == NULL)
		return NULL;
			
	tpd->status = TPD_ADDR(mapping);
	tpd->reserved = 0; 
	tpd->iovec[0].addr = 0; tpd->iovec[0].len = 0;
	tpd->iovec[1].addr = 0; tpd->iovec[1].len = 0;
	tpd->iovec[2].addr = 0; tpd->iovec[2].len = 0;

	return tpd;
}
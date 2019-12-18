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
struct TYPE_2__ {int /*<<< orphan*/  ci; int /*<<< orphan*/  ce_be; int /*<<< orphan*/  ce; } ;
struct bm_portal {TYPE_1__ addr; } ;
struct bman_portal {struct bm_portal_config const* config; int /*<<< orphan*/  irqname; scalar_t__ irq_sources; struct bm_portal p; } ;
struct bm_portal_config {int /*<<< orphan*/  irq; int /*<<< orphan*/  dev; int /*<<< orphan*/  cpu; int /*<<< orphan*/  addr_virt_ci; int /*<<< orphan*/  addr_virt_ce; } ;

/* Variables and functions */
 int /*<<< orphan*/  BM_REG_IER ; 
 int /*<<< orphan*/  BM_REG_IIR ; 
 int /*<<< orphan*/  BM_REG_ISDR ; 
 int /*<<< orphan*/  BM_REG_ISR ; 
 int EIO ; 
 char* IRQNAME ; 
 int /*<<< orphan*/  MAX_IRQNAME ; 
 int /*<<< orphan*/  bm_isr_bscn_disable (struct bm_portal*) ; 
 int /*<<< orphan*/  bm_mc_finish (struct bm_portal*) ; 
 scalar_t__ bm_mc_init (struct bm_portal*) ; 
 int /*<<< orphan*/  bm_out (struct bm_portal*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bm_rcr_cce ; 
 int /*<<< orphan*/  bm_rcr_finish (struct bm_portal*) ; 
 int bm_rcr_get_fill (struct bm_portal*) ; 
 scalar_t__ bm_rcr_init (struct bm_portal*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bm_rcr_pvb ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ dpaa_set_portal_irq_affinity (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct bman_portal*) ; 
 int /*<<< orphan*/  portal_isr ; 
 scalar_t__ request_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct bman_portal*) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int bman_create_portal(struct bman_portal *portal,
			      const struct bm_portal_config *c)
{
	struct bm_portal *p;
	int ret;

	p = &portal->p;
	/*
	 * prep the low-level portal struct with the mapped addresses from the
	 * config, everything that follows depends on it and "config" is more
	 * for (de)reference...
	 */
	p->addr.ce = c->addr_virt_ce;
	p->addr.ce_be = c->addr_virt_ce;
	p->addr.ci = c->addr_virt_ci;
	if (bm_rcr_init(p, bm_rcr_pvb, bm_rcr_cce)) {
		dev_err(c->dev, "RCR initialisation failed\n");
		goto fail_rcr;
	}
	if (bm_mc_init(p)) {
		dev_err(c->dev, "MC initialisation failed\n");
		goto fail_mc;
	}
	/*
	 * Default to all BPIDs disabled, we enable as required at
	 * run-time.
	 */
	bm_isr_bscn_disable(p);

	/* Write-to-clear any stale interrupt status bits */
	bm_out(p, BM_REG_ISDR, 0xffffffff);
	portal->irq_sources = 0;
	bm_out(p, BM_REG_IER, 0);
	bm_out(p, BM_REG_ISR, 0xffffffff);
	snprintf(portal->irqname, MAX_IRQNAME, IRQNAME, c->cpu);
	if (request_irq(c->irq, portal_isr, 0, portal->irqname,	portal)) {
		dev_err(c->dev, "request_irq() failed\n");
		goto fail_irq;
	}

	if (dpaa_set_portal_irq_affinity(c->dev, c->irq, c->cpu))
		goto fail_affinity;

	/* Need RCR to be empty before continuing */
	ret = bm_rcr_get_fill(p);
	if (ret) {
		dev_err(c->dev, "RCR unclean\n");
		goto fail_rcr_empty;
	}
	/* Success */
	portal->config = c;

	bm_out(p, BM_REG_ISDR, 0);
	bm_out(p, BM_REG_IIR, 0);

	return 0;

fail_rcr_empty:
fail_affinity:
	free_irq(c->irq, portal);
fail_irq:
	bm_mc_finish(p);
fail_mc:
	bm_rcr_finish(p);
fail_rcr:
	return -EIO;
}
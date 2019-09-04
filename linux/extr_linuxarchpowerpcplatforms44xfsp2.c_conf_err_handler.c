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
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  DCRN_CONF_FIR_RWC ; 
 int /*<<< orphan*/  DCRN_CONF_RPERR0 ; 
 int /*<<< orphan*/  DCRN_CONF_RPERR1 ; 
 int /*<<< orphan*/  mfdcr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  panic (char*) ; 
 int /*<<< orphan*/  pr_err (char*,...) ; 

__attribute__((used)) static irqreturn_t conf_err_handler(int irq, void *data) {
	pr_err("Configuration Logic Error\n");
	pr_err("CONF_FIR: 0x%08x\n", mfdcr(DCRN_CONF_FIR_RWC));
	pr_err("RPERR0:   0x%08x\n", mfdcr(DCRN_CONF_RPERR0));
	pr_err("RPERR1:   0x%08x\n", mfdcr(DCRN_CONF_RPERR1));
	panic("Configuration Logic Error\n");
}
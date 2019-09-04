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
 int /*<<< orphan*/  CMUN_FIR0 ; 
 int /*<<< orphan*/  mfcmu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  panic (char*) ; 
 int /*<<< orphan*/  pr_err (char*,...) ; 

__attribute__((used)) static irqreturn_t cmu_err_handler(int irq, void *data) {
	pr_err("CMU Error\n");
	pr_err("FIR0: 0x%08x\n", mfcmu(CMUN_FIR0));
	panic("CMU Error\n");
}
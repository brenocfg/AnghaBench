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
struct cc_drvdata {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CC_REG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HOST_IMR ; 
 int /*<<< orphan*/  cc_iowrite (struct cc_drvdata*,int /*<<< orphan*/ ,int) ; 

void fini_cc_regs(struct cc_drvdata *drvdata)
{
	/* Mask all interrupts */
	cc_iowrite(drvdata, CC_REG(HOST_IMR), 0xFFFFFFFF);
}
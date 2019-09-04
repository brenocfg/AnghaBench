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
typedef  int u64 ;
struct TYPE_2__ {scalar_t__ reg_base; } ;

/* Variables and functions */
 int CLKRX_BYP ; 
 int CLK_RESET ; 
 int COMP_EN ; 
 int DLL_RESET ; 
 int PORT_EN ; 
 scalar_t__ XCV_DLL_CTL ; 
 scalar_t__ XCV_RESET ; 
 int /*<<< orphan*/  msleep (int) ; 
 int readq_relaxed (scalar_t__) ; 
 int /*<<< orphan*/  writeq_relaxed (int,scalar_t__) ; 
 TYPE_1__* xcv ; 

void xcv_init_hw(void)
{
	u64  cfg;

	/* Take DLL out of reset */
	cfg = readq_relaxed(xcv->reg_base + XCV_RESET);
	cfg &= ~DLL_RESET;
	writeq_relaxed(cfg, xcv->reg_base + XCV_RESET);

	/* Take clock tree out of reset */
	cfg = readq_relaxed(xcv->reg_base + XCV_RESET);
	cfg &= ~CLK_RESET;
	writeq_relaxed(cfg, xcv->reg_base + XCV_RESET);
	/* Wait for DLL to lock */
	msleep(1);

	/* Configure DLL - enable or bypass
	 * TX no bypass, RX bypass
	 */
	cfg = readq_relaxed(xcv->reg_base + XCV_DLL_CTL);
	cfg &= ~0xFF03;
	cfg |= CLKRX_BYP;
	writeq_relaxed(cfg, xcv->reg_base + XCV_DLL_CTL);

	/* Enable compensation controller and force the
	 * write to be visible to HW by readig back.
	 */
	cfg = readq_relaxed(xcv->reg_base + XCV_RESET);
	cfg |= COMP_EN;
	writeq_relaxed(cfg, xcv->reg_base + XCV_RESET);
	readq_relaxed(xcv->reg_base + XCV_RESET);
	/* Wait for compensation state machine to lock */
	msleep(10);

	/* enable the XCV block */
	cfg = readq_relaxed(xcv->reg_base + XCV_RESET);
	cfg |= PORT_EN;
	writeq_relaxed(cfg, xcv->reg_base + XCV_RESET);

	cfg = readq_relaxed(xcv->reg_base + XCV_RESET);
	cfg |= CLK_RESET;
	writeq_relaxed(cfg, xcv->reg_base + XCV_RESET);
}
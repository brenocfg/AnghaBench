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
typedef  int /*<<< orphan*/  uint32_t ;
struct stfsm {scalar_t__ base; } ;

/* Variables and functions */
 int EBUSY ; 
 scalar_t__ SPI_MODESELECT ; 
 scalar_t__ SPI_STA_MODE_CHANGE ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  udelay (int) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int stfsm_set_mode(struct stfsm *fsm, uint32_t mode)
{
	int ret, timeout = 10;

	/* Wait for controller to accept mode change */
	while (--timeout) {
		ret = readl(fsm->base + SPI_STA_MODE_CHANGE);
		if (ret & 0x1)
			break;
		udelay(1);
	}

	if (!timeout)
		return -EBUSY;

	writel(mode, fsm->base + SPI_MODESELECT);

	return 0;
}
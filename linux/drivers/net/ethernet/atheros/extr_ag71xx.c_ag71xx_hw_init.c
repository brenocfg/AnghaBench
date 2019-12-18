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
struct ag71xx {int /*<<< orphan*/  mac_reset; } ;

/* Variables and functions */
 int /*<<< orphan*/  AG71XX_REG_MAC_CFG1 ; 
 int /*<<< orphan*/  MAC_CFG1_SR ; 
 int /*<<< orphan*/  ag71xx_dma_reset (struct ag71xx*) ; 
 int /*<<< orphan*/  ag71xx_hw_setup (struct ag71xx*) ; 
 int /*<<< orphan*/  ag71xx_hw_stop (struct ag71xx*) ; 
 int /*<<< orphan*/  ag71xx_sb (struct ag71xx*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  reset_control_assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reset_control_deassert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static void ag71xx_hw_init(struct ag71xx *ag)
{
	ag71xx_hw_stop(ag);

	ag71xx_sb(ag, AG71XX_REG_MAC_CFG1, MAC_CFG1_SR);
	usleep_range(20, 30);

	reset_control_assert(ag->mac_reset);
	msleep(100);
	reset_control_deassert(ag->mac_reset);
	msleep(200);

	ag71xx_hw_setup(ag);

	ag71xx_dma_reset(ag);
}
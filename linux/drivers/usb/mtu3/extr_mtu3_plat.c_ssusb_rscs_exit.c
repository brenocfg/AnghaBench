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
struct ssusb_mtk {int /*<<< orphan*/  vusb33; } ;

/* Variables and functions */
 int /*<<< orphan*/  regulator_disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ssusb_clks_disable (struct ssusb_mtk*) ; 
 int /*<<< orphan*/  ssusb_phy_exit (struct ssusb_mtk*) ; 
 int /*<<< orphan*/  ssusb_phy_power_off (struct ssusb_mtk*) ; 

__attribute__((used)) static void ssusb_rscs_exit(struct ssusb_mtk *ssusb)
{
	ssusb_clks_disable(ssusb);
	regulator_disable(ssusb->vusb33);
	ssusb_phy_power_off(ssusb);
	ssusb_phy_exit(ssusb);
}
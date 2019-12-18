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
struct ssusb_mtk {int /*<<< orphan*/  ippc_base; } ;

/* Variables and functions */
 int /*<<< orphan*/  SSUSB_IP_DEV_PDN ; 
 int /*<<< orphan*/  SSUSB_IP_SW_RST ; 
 int /*<<< orphan*/  U3D_SSUSB_IP_PW_CTRL0 ; 
 int /*<<< orphan*/  U3D_SSUSB_IP_PW_CTRL2 ; 
 int /*<<< orphan*/  mtu3_clrbits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtu3_setbits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void ssusb_ip_sw_reset(struct ssusb_mtk *ssusb)
{
	/* reset whole ip (xhci & u3d) */
	mtu3_setbits(ssusb->ippc_base, U3D_SSUSB_IP_PW_CTRL0, SSUSB_IP_SW_RST);
	udelay(1);
	mtu3_clrbits(ssusb->ippc_base, U3D_SSUSB_IP_PW_CTRL0, SSUSB_IP_SW_RST);

	/*
	 * device ip may be powered on in firmware/BROM stage before entering
	 * kernel stage;
	 * power down device ip, otherwise ip-sleep will fail when working as
	 * host only mode
	 */
	mtu3_setbits(ssusb->ippc_base, U3D_SSUSB_IP_PW_CTRL2, SSUSB_IP_DEV_PDN);
}
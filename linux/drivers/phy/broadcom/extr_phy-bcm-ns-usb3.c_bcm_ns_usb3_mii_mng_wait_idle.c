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
struct bcm_ns_usb3 {scalar_t__ ccb_mii; } ;

/* Variables and functions */
 scalar_t__ BCMA_CCB_MII_MNG_CTL ; 
 int /*<<< orphan*/  BCM_NS_USB3_MII_MNG_TIMEOUT_US ; 
 int bcm_ns_usb3_wait_reg (struct bcm_ns_usb3*,scalar_t__,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usecs_to_jiffies (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int bcm_ns_usb3_mii_mng_wait_idle(struct bcm_ns_usb3 *usb3)
{
	return bcm_ns_usb3_wait_reg(usb3, usb3->ccb_mii + BCMA_CCB_MII_MNG_CTL,
				    0x0100, 0x0000,
				    usecs_to_jiffies(BCM_NS_USB3_MII_MNG_TIMEOUT_US));
}
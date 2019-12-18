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
typedef  int u32 ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int BIT30 ; 
 int BIT31 ; 
 int /*<<< orphan*/  RWCAM ; 
 int /*<<< orphan*/  rtl92e_writel (struct net_device*,int /*<<< orphan*/ ,int) ; 

void rtl92e_cam_reset(struct net_device *dev)
{
	u32 ulcommand = 0;

	ulcommand |= BIT31|BIT30;
	rtl92e_writel(dev, RWCAM, ulcommand);
}
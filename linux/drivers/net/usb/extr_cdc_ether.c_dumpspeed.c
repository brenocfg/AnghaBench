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
struct usbnet {int /*<<< orphan*/  net; } ;
typedef  int /*<<< orphan*/  __le32 ;

/* Variables and functions */
 int __le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_info (struct usbnet*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,int) ; 
 int /*<<< orphan*/  timer ; 

__attribute__((used)) static void dumpspeed(struct usbnet *dev, __le32 *speeds)
{
	netif_info(dev, timer, dev->net,
		   "link speeds: %u kbps up, %u kbps down\n",
		   __le32_to_cpu(speeds[0]) / 1000,
		   __le32_to_cpu(speeds[1]) / 1000);
}
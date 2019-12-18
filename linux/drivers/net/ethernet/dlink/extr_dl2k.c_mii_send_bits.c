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
 int /*<<< orphan*/  mii_sendbit (struct net_device*,int) ; 

__attribute__((used)) static void
mii_send_bits (struct net_device *dev, u32 data, int len)
{
	int i;

	for (i = len - 1; i >= 0; i--) {
		mii_sendbit (dev, data & (1 << i));
	}
}
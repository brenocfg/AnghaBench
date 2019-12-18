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
struct phy_dev {int dummy; } ;

/* Variables and functions */
 int gdm_lte_receive_pkt (struct phy_dev*,void*,int) ; 

__attribute__((used)) static int rx_complete(void *arg, void *data, int len, int context)
{
	struct phy_dev *phy_dev = arg;

	return gdm_lte_receive_pkt(phy_dev, data, len);
}
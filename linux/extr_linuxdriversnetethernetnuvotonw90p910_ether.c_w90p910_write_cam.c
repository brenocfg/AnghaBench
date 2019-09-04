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
struct w90p910_ether {scalar_t__ reg; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 unsigned int CAM_ENTRY_SIZE ; 
 scalar_t__ REG_CAML_BASE ; 
 scalar_t__ REG_CAMM_BASE ; 
 int /*<<< orphan*/  __raw_writel (unsigned int,scalar_t__) ; 
 struct w90p910_ether* netdev_priv (struct net_device*) ; 

__attribute__((used)) static void w90p910_write_cam(struct net_device *dev,
				unsigned int x, unsigned char *pval)
{
	struct w90p910_ether *ether = netdev_priv(dev);
	unsigned int msw, lsw;

	msw = (pval[0] << 24) | (pval[1] << 16) | (pval[2] << 8) | pval[3];

	lsw = (pval[4] << 24) | (pval[5] << 16);

	__raw_writel(lsw, ether->reg + REG_CAML_BASE + x * CAM_ENTRY_SIZE);
	__raw_writel(msw, ether->reg + REG_CAMM_BASE + x * CAM_ENTRY_SIZE);
}
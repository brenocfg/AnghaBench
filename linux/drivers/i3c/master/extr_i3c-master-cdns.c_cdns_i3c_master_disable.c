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
struct cdns_i3c_master {scalar_t__ regs; } ;

/* Variables and functions */
 scalar_t__ CTRL ; 
 int CTRL_DEV_EN ; 
 scalar_t__ MST_STATUS0 ; 
 int MST_STATUS0_IDLE ; 
 int readl (scalar_t__) ; 
 int readl_poll_timeout (scalar_t__,int,int,int,int) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static int cdns_i3c_master_disable(struct cdns_i3c_master *master)
{
	u32 status;

	writel(readl(master->regs + CTRL) & ~CTRL_DEV_EN, master->regs + CTRL);

	return readl_poll_timeout(master->regs + MST_STATUS0, status,
				  status & MST_STATUS0_IDLE, 10, 1000000);
}
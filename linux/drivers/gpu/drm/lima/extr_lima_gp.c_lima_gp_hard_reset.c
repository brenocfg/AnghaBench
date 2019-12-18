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
struct lima_ip {struct lima_device* dev; } ;
struct lima_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  LIMA_GP_CMD ; 
 int LIMA_GP_CMD_RESET ; 
 int /*<<< orphan*/  LIMA_GP_INT_CLEAR ; 
 int /*<<< orphan*/  LIMA_GP_INT_MASK ; 
 int LIMA_GP_IRQ_MASK_ALL ; 
 int LIMA_GP_IRQ_MASK_USED ; 
 int /*<<< orphan*/  LIMA_GP_PERF_CNT_0_LIMIT ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  gp_write (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  lima_gp_hard_reset_poll ; 
 int lima_poll_timeout (struct lima_ip*,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int lima_gp_hard_reset(struct lima_ip *ip)
{
	struct lima_device *dev = ip->dev;
	int ret;

	gp_write(LIMA_GP_PERF_CNT_0_LIMIT, 0xC0FFE000);
	gp_write(LIMA_GP_INT_MASK, 0);
	gp_write(LIMA_GP_CMD, LIMA_GP_CMD_RESET);
	ret = lima_poll_timeout(ip, lima_gp_hard_reset_poll, 10, 100);
	if (ret) {
		dev_err(dev->dev, "gp hard reset timeout\n");
		return ret;
	}

	gp_write(LIMA_GP_PERF_CNT_0_LIMIT, 0);
	gp_write(LIMA_GP_INT_CLEAR, LIMA_GP_IRQ_MASK_ALL);
	gp_write(LIMA_GP_INT_MASK, LIMA_GP_IRQ_MASK_USED);
	return 0;
}
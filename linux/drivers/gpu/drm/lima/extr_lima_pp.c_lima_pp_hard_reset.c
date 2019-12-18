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
 int /*<<< orphan*/  LIMA_PP_CTRL ; 
 int LIMA_PP_CTRL_FORCE_RESET ; 
 int /*<<< orphan*/  LIMA_PP_INT_CLEAR ; 
 int /*<<< orphan*/  LIMA_PP_INT_MASK ; 
 int LIMA_PP_IRQ_MASK_ALL ; 
 int LIMA_PP_IRQ_MASK_USED ; 
 int /*<<< orphan*/  LIMA_PP_PERF_CNT_0_LIMIT ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int lima_poll_timeout (struct lima_ip*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  lima_pp_hard_reset_poll ; 
 int /*<<< orphan*/  pp_write (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int lima_pp_hard_reset(struct lima_ip *ip)
{
	struct lima_device *dev = ip->dev;
	int ret;

	pp_write(LIMA_PP_PERF_CNT_0_LIMIT, 0xC0FFE000);
	pp_write(LIMA_PP_INT_MASK, 0);
	pp_write(LIMA_PP_CTRL, LIMA_PP_CTRL_FORCE_RESET);
	ret = lima_poll_timeout(ip, lima_pp_hard_reset_poll, 10, 100);
	if (ret) {
		dev_err(dev->dev, "pp hard reset timeout\n");
		return ret;
	}

	pp_write(LIMA_PP_PERF_CNT_0_LIMIT, 0);
	pp_write(LIMA_PP_INT_CLEAR, LIMA_PP_IRQ_MASK_ALL);
	pp_write(LIMA_PP_INT_MASK, LIMA_PP_IRQ_MASK_USED);
	return 0;
}
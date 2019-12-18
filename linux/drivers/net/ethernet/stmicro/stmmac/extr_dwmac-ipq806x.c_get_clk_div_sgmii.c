#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct ipq806x_gmac {TYPE_1__* pdev; } ;
struct device {int dummy; } ;
struct TYPE_2__ {struct device dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int NSS_COMMON_CLK_DIV_SGMII_10 ; 
 int NSS_COMMON_CLK_DIV_SGMII_100 ; 
 int NSS_COMMON_CLK_DIV_SGMII_1000 ; 
#define  SPEED_10 130 
#define  SPEED_100 129 
#define  SPEED_1000 128 
 int /*<<< orphan*/  dev_err (struct device*,char*,unsigned int) ; 

__attribute__((used)) static int get_clk_div_sgmii(struct ipq806x_gmac *gmac, unsigned int speed)
{
	struct device *dev = &gmac->pdev->dev;
	int div;

	switch (speed) {
	case SPEED_1000:
		div = NSS_COMMON_CLK_DIV_SGMII_1000;
		break;

	case SPEED_100:
		div = NSS_COMMON_CLK_DIV_SGMII_100;
		break;

	case SPEED_10:
		div = NSS_COMMON_CLK_DIV_SGMII_10;
		break;

	default:
		dev_err(dev, "Speed %dMbps not supported in SGMII\n", speed);
		return -EINVAL;
	}

	return div;
}
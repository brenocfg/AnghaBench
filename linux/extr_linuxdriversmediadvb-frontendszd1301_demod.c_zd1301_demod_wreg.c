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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct zd1301_demod_platform_data {int (* reg_write ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  reg_priv; } ;
struct zd1301_demod_dev {struct platform_device* pdev; } ;
struct TYPE_2__ {struct zd1301_demod_platform_data* platform_data; } ;
struct platform_device {TYPE_1__ dev; } ;

/* Variables and functions */
 int stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int zd1301_demod_wreg(struct zd1301_demod_dev *dev, u16 reg, u8 val)
{
	struct platform_device *pdev = dev->pdev;
	struct zd1301_demod_platform_data *pdata = pdev->dev.platform_data;

	return pdata->reg_write(pdata->reg_priv, reg, val);
}
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
struct stu300_dev {scalar_t__ virtbase; int /*<<< orphan*/  adapter; } ;
struct platform_device {int dummy; } ;

/* Variables and functions */
 scalar_t__ I2C_CR ; 
 int /*<<< orphan*/  i2c_del_adapter (int /*<<< orphan*/ *) ; 
 struct stu300_dev* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  stu300_wr8 (int,scalar_t__) ; 

__attribute__((used)) static int stu300_remove(struct platform_device *pdev)
{
	struct stu300_dev *dev = platform_get_drvdata(pdev);

	i2c_del_adapter(&dev->adapter);
	/* Turn off everything */
	stu300_wr8(0x00, dev->virtbase + I2C_CR);
	return 0;
}
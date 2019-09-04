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
struct s3c2410_platform_nand {int dummy; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 struct s3c2410_platform_nand* dev_get_platdata (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct s3c2410_platform_nand *to_nand_plat(struct platform_device *dev)
{
	return dev_get_platdata(&dev->dev);
}
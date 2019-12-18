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
struct platform_device {int dummy; } ;
struct i2c_device {int /*<<< orphan*/  adapter; } ;

/* Variables and functions */
 int /*<<< orphan*/  i2c_del_adapter (int /*<<< orphan*/ *) ; 
 scalar_t__ platform_get_drvdata (struct platform_device*) ; 

__attribute__((used)) static int pi2c_remove(struct platform_device *pldev)
{
	struct i2c_device *lddev;

	lddev = (struct i2c_device *)platform_get_drvdata(pldev);

	i2c_del_adapter(&lddev->adapter);

	//TODO: Figure out the right thing to do here...
	//pci_write_config_byte(dev, SMBHSTCFG, priv->original_hstcfg);
	//pci_release_region(dev, SMBBAR);
	//pci_set_drvdata(dev, NULL);

	//cdev_del(&lddev->cdev);

	return 0;
}
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
struct pcf50633 {int /*<<< orphan*/ * regulator_pdev; int /*<<< orphan*/  bl_pdev; int /*<<< orphan*/  adc_pdev; int /*<<< orphan*/  mbc_pdev; int /*<<< orphan*/  rtc_pdev; int /*<<< orphan*/  input_pdev; } ;
struct TYPE_2__ {int /*<<< orphan*/  kobj; } ;
struct i2c_client {TYPE_1__ dev; } ;

/* Variables and functions */
 int PCF50633_NUM_REGULATORS ; 
 struct pcf50633* i2c_get_clientdata (struct i2c_client*) ; 
 int /*<<< orphan*/  pcf50633_irq_free (struct pcf50633*) ; 
 int /*<<< orphan*/  pcf_attr_group ; 
 int /*<<< orphan*/  platform_device_unregister (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sysfs_remove_group (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int pcf50633_remove(struct i2c_client *client)
{
	struct pcf50633 *pcf = i2c_get_clientdata(client);
	int i;

	sysfs_remove_group(&client->dev.kobj, &pcf_attr_group);
	pcf50633_irq_free(pcf);

	platform_device_unregister(pcf->input_pdev);
	platform_device_unregister(pcf->rtc_pdev);
	platform_device_unregister(pcf->mbc_pdev);
	platform_device_unregister(pcf->adc_pdev);
	platform_device_unregister(pcf->bl_pdev);

	for (i = 0; i < PCF50633_NUM_REGULATORS; i++)
		platform_device_unregister(pcf->regulator_pdev[i]);

	return 0;
}
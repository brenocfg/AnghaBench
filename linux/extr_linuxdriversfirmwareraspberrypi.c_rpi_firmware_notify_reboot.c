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
struct rpi_firmware {int dummy; } ;
struct platform_device {int dummy; } ;
struct notifier_block {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  RPI_FIRMWARE_NOTIFY_REBOOT ; 
 struct platform_device* g_pdev ; 
 struct rpi_firmware* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  rpi_firmware_property (struct rpi_firmware*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int rpi_firmware_notify_reboot(struct notifier_block *nb,
				      unsigned long action,
				      void *data)
{
	struct rpi_firmware *fw;
	struct platform_device *pdev = g_pdev;

	if (!pdev)
		return 0;

	fw = platform_get_drvdata(pdev);
	if (!fw)
		return 0;

	(void)rpi_firmware_property(fw, RPI_FIRMWARE_NOTIFY_REBOOT,
				    0, 0);

	return 0;
}
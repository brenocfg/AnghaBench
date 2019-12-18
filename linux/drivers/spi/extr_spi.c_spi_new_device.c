#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {void* platform_data; } ;
struct spi_device {TYPE_1__ dev; int /*<<< orphan*/ * controller_state; int /*<<< orphan*/  controller_data; int /*<<< orphan*/  modalias; int /*<<< orphan*/  irq; int /*<<< orphan*/  mode; int /*<<< orphan*/  max_speed_hz; int /*<<< orphan*/  chip_select; } ;
struct spi_controller {int /*<<< orphan*/  dev; } ;
struct spi_board_info {int /*<<< orphan*/  properties; int /*<<< orphan*/  modalias; int /*<<< orphan*/  controller_data; scalar_t__ platform_data; int /*<<< orphan*/  irq; int /*<<< orphan*/  mode; int /*<<< orphan*/  max_speed_hz; int /*<<< orphan*/  chip_select; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int) ; 
 int device_add_properties (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_remove_properties (TYPE_1__*) ; 
 int spi_add_device (struct spi_device*) ; 
 struct spi_device* spi_alloc_device (struct spi_controller*) ; 
 int /*<<< orphan*/  spi_dev_put (struct spi_device*) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int strlen (int /*<<< orphan*/ ) ; 

struct spi_device *spi_new_device(struct spi_controller *ctlr,
				  struct spi_board_info *chip)
{
	struct spi_device	*proxy;
	int			status;

	/* NOTE:  caller did any chip->bus_num checks necessary.
	 *
	 * Also, unless we change the return value convention to use
	 * error-or-pointer (not NULL-or-pointer), troubleshootability
	 * suggests syslogged diagnostics are best here (ugh).
	 */

	proxy = spi_alloc_device(ctlr);
	if (!proxy)
		return NULL;

	WARN_ON(strlen(chip->modalias) >= sizeof(proxy->modalias));

	proxy->chip_select = chip->chip_select;
	proxy->max_speed_hz = chip->max_speed_hz;
	proxy->mode = chip->mode;
	proxy->irq = chip->irq;
	strlcpy(proxy->modalias, chip->modalias, sizeof(proxy->modalias));
	proxy->dev.platform_data = (void *) chip->platform_data;
	proxy->controller_data = chip->controller_data;
	proxy->controller_state = NULL;

	if (chip->properties) {
		status = device_add_properties(&proxy->dev, chip->properties);
		if (status) {
			dev_err(&ctlr->dev,
				"failed to add properties to '%s': %d\n",
				chip->modalias, status);
			goto err_dev_put;
		}
	}

	status = spi_add_device(proxy);
	if (status < 0)
		goto err_remove_props;

	return proxy;

err_remove_props:
	if (chip->properties)
		device_remove_properties(&proxy->dev);
err_dev_put:
	spi_dev_put(proxy);
	return NULL;
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct firmware {int dummy; } ;
struct device {int dummy; } ;
struct cyapa {TYPE_2__* ops; TYPE_1__* client; } ;
struct TYPE_4__ {int (* check_fw ) (struct cyapa*,struct firmware const*) ;int (* bl_enter ) (struct cyapa*) ;int (* bl_activate ) (struct cyapa*) ;int (* bl_initiate ) (struct cyapa*,struct firmware const*) ;int (* update_fw ) (struct cyapa*,struct firmware const*) ;} ;
struct TYPE_3__ {struct device dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  cyapa_disable_irq_for_cmd (struct cyapa*) ; 
 int /*<<< orphan*/  cyapa_enable_irq_for_cmd (struct cyapa*) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 int /*<<< orphan*/  pm_runtime_get_sync (struct device*) ; 
 int /*<<< orphan*/  pm_runtime_put_noidle (struct device*) ; 
 int /*<<< orphan*/  release_firmware (struct firmware const*) ; 
 int request_firmware (struct firmware const**,char const*,struct device*) ; 
 int stub1 (struct cyapa*,struct firmware const*) ; 
 int stub2 (struct cyapa*) ; 
 int stub3 (struct cyapa*) ; 
 int stub4 (struct cyapa*,struct firmware const*) ; 
 int stub5 (struct cyapa*,struct firmware const*) ; 

__attribute__((used)) static int cyapa_firmware(struct cyapa *cyapa, const char *fw_name)
{
	struct device *dev = &cyapa->client->dev;
	const struct firmware *fw;
	int error;

	error = request_firmware(&fw, fw_name, dev);
	if (error) {
		dev_err(dev, "Could not load firmware from %s: %d\n",
			fw_name, error);
		return error;
	}

	error = cyapa->ops->check_fw(cyapa, fw);
	if (error) {
		dev_err(dev, "Invalid CYAPA firmware image: %s\n",
				fw_name);
		goto done;
	}

	/*
	 * Resume the potentially suspended device because doing FW
	 * update on a device not in the FULL mode has a chance to
	 * fail.
	 */
	pm_runtime_get_sync(dev);

	/* Require IRQ support for firmware update commands. */
	cyapa_enable_irq_for_cmd(cyapa);

	error = cyapa->ops->bl_enter(cyapa);
	if (error) {
		dev_err(dev, "bl_enter failed, %d\n", error);
		goto err_detect;
	}

	error = cyapa->ops->bl_activate(cyapa);
	if (error) {
		dev_err(dev, "bl_activate failed, %d\n", error);
		goto err_detect;
	}

	error = cyapa->ops->bl_initiate(cyapa, fw);
	if (error) {
		dev_err(dev, "bl_initiate failed, %d\n", error);
		goto err_detect;
	}

	error = cyapa->ops->update_fw(cyapa, fw);
	if (error) {
		dev_err(dev, "update_fw failed, %d\n", error);
		goto err_detect;
	}

err_detect:
	cyapa_disable_irq_for_cmd(cyapa);
	pm_runtime_put_noidle(dev);

done:
	release_firmware(fw);
	return error;
}
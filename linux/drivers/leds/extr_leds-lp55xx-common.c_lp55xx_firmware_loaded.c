#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct lp55xx_chip {int engine_idx; struct firmware const* fw; int /*<<< orphan*/  lock; TYPE_3__* cfg; TYPE_2__* engines; TYPE_1__* cl; } ;
struct firmware {int dummy; } ;
struct device {int dummy; } ;
typedef  enum lp55xx_engine_index { ____Placeholder_lp55xx_engine_index } lp55xx_engine_index ;
struct TYPE_6__ {int /*<<< orphan*/  (* firmware_cb ) (struct lp55xx_chip*) ;} ;
struct TYPE_5__ {int /*<<< orphan*/  mode; } ;
struct TYPE_4__ {struct device dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  LP55XX_ENGINE_LOAD ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  release_firmware (struct firmware const*) ; 
 int /*<<< orphan*/  stub1 (struct lp55xx_chip*) ; 

__attribute__((used)) static void lp55xx_firmware_loaded(const struct firmware *fw, void *context)
{
	struct lp55xx_chip *chip = context;
	struct device *dev = &chip->cl->dev;
	enum lp55xx_engine_index idx = chip->engine_idx;

	if (!fw) {
		dev_err(dev, "firmware request failed\n");
		return;
	}

	/* handling firmware data is chip dependent */
	mutex_lock(&chip->lock);

	chip->engines[idx - 1].mode = LP55XX_ENGINE_LOAD;
	chip->fw = fw;
	if (chip->cfg->firmware_cb)
		chip->cfg->firmware_cb(chip);

	mutex_unlock(&chip->lock);

	/* firmware should be released for other channel use */
	release_firmware(chip->fw);
	chip->fw = NULL;
}
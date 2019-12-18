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
struct bq24257_device {int /*<<< orphan*/ * pg; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  BQ24257_PG_GPIO ; 
 int /*<<< orphan*/  EPROBE_DEFER ; 
 int /*<<< orphan*/  GPIOD_IN ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PTR_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  desc_to_gpio (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/ * devm_gpiod_get_optional (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void bq24257_pg_gpio_probe(struct bq24257_device *bq)
{
	bq->pg = devm_gpiod_get_optional(bq->dev, BQ24257_PG_GPIO, GPIOD_IN);

	if (PTR_ERR(bq->pg) == -EPROBE_DEFER) {
		dev_info(bq->dev, "probe retry requested for PG pin\n");
		return;
	} else if (IS_ERR(bq->pg)) {
		dev_err(bq->dev, "error probing PG pin\n");
		bq->pg = NULL;
		return;
	}

	if (bq->pg)
		dev_dbg(bq->dev, "probed PG pin = %d\n", desc_to_gpio(bq->pg));
}
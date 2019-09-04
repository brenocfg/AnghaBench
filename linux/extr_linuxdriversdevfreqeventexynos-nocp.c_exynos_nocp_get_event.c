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
struct exynos_nocp {int /*<<< orphan*/  dev; int /*<<< orphan*/  regmap; } ;
struct devfreq_event_dev {TYPE_1__* desc; int /*<<< orphan*/  dev; } ;
struct devfreq_event_data {unsigned int load_count; unsigned int total_count; } ;
struct TYPE_2__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  NOCP_COUNTERS_0_VAL ; 
 int /*<<< orphan*/  NOCP_COUNTERS_1_VAL ; 
 int /*<<< orphan*/  NOCP_COUNTERS_2_VAL ; 
 int /*<<< orphan*/  NOCP_COUNTERS_3_VAL ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 struct exynos_nocp* devfreq_event_get_drvdata (struct devfreq_event_dev*) ; 
 int regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int*) ; 

__attribute__((used)) static int exynos_nocp_get_event(struct devfreq_event_dev *edev,
				struct devfreq_event_data *edata)
{
	struct exynos_nocp *nocp = devfreq_event_get_drvdata(edev);
	unsigned int counter[4];
	int ret;

	/* Read cycle count */
	ret = regmap_read(nocp->regmap, NOCP_COUNTERS_0_VAL, &counter[0]);
	if (ret < 0)
		goto out;

	ret = regmap_read(nocp->regmap, NOCP_COUNTERS_1_VAL, &counter[1]);
	if (ret < 0)
		goto out;

	ret = regmap_read(nocp->regmap, NOCP_COUNTERS_2_VAL, &counter[2]);
	if (ret < 0)
		goto out;

	ret = regmap_read(nocp->regmap, NOCP_COUNTERS_3_VAL, &counter[3]);
	if (ret < 0)
		goto out;

	edata->load_count = ((counter[1] << 16) | counter[0]);
	edata->total_count = ((counter[3] << 16) | counter[2]);

	dev_dbg(&edev->dev, "%s (event: %ld/%ld)\n", edev->desc->name,
					edata->load_count, edata->total_count);

	return 0;

out:
	dev_err(nocp->dev, "Failed to read the counter of NoC probe device\n");

	return ret;
}
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
struct madera {int /*<<< orphan*/  dev; int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  MADERA_SOFTWARE_RESET ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static int madera_soft_reset(struct madera *madera)
{
	int ret;

	ret = regmap_write(madera->regmap, MADERA_SOFTWARE_RESET, 0);
	if (ret != 0) {
		dev_err(madera->dev, "Failed to soft reset device: %d\n", ret);
		return ret;
	}

	/* Allow time for internal clocks to startup after reset */
	usleep_range(1000, 2000);

	return 0;
}
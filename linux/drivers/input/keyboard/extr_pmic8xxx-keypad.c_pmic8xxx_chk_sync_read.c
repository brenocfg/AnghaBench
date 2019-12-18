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
struct pmic8xxx_kp {int /*<<< orphan*/  dev; int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int DIV_ROUND_UP (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  KEYP_CLOCK_FREQ ; 
 int /*<<< orphan*/  KEYP_SCAN ; 
 int /*<<< orphan*/  USEC_PER_SEC ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int*) ; 
 int regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int pmic8xxx_chk_sync_read(struct pmic8xxx_kp *kp)
{
	int rc;
	unsigned int scan_val;

	rc = regmap_read(kp->regmap, KEYP_SCAN, &scan_val);
	if (rc < 0) {
		dev_err(kp->dev, "Error reading KEYP_SCAN reg, rc=%d\n", rc);
		return rc;
	}

	scan_val |= 0x1;

	rc = regmap_write(kp->regmap, KEYP_SCAN, scan_val);
	if (rc < 0) {
		dev_err(kp->dev, "Error writing KEYP_SCAN reg, rc=%d\n", rc);
		return rc;
	}

	/* 2 * 32KHz clocks */
	udelay((2 * DIV_ROUND_UP(USEC_PER_SEC, KEYP_CLOCK_FREQ)) + 1);

	return rc;
}
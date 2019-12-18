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
typedef  int u8 ;
struct pm2xxx_charger {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int PM2XXX_INT2_S_ITVPWR1PLUG ; 
 int PM2XXX_INT2_S_ITVPWR2PLUG ; 
 int /*<<< orphan*/  PM2XXX_SRCE_REG_INT2 ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int pm2xxx_reg_read (struct pm2xxx_charger*,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static int pm2xxx_charger_detection(struct pm2xxx_charger *pm2, u8 *val)
{
	int ret;

	ret = pm2xxx_reg_read(pm2, PM2XXX_SRCE_REG_INT2, val);

	if (ret < 0) {
		dev_err(pm2->dev, "Charger detection failed\n");
		goto out;
	}

	*val &= (PM2XXX_INT2_S_ITVPWR1PLUG | PM2XXX_INT2_S_ITVPWR2PLUG);

out:
	return ret;
}
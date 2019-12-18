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
struct tps65217_bl_pdata {int isel; int /*<<< orphan*/  fdim; } ;
struct tps65217_bl {int /*<<< orphan*/  dev; int /*<<< orphan*/  tps; } ;

/* Variables and functions */
 int EINVAL ; 
#define  TPS65217_BL_ISET1 129 
#define  TPS65217_BL_ISET2 128 
 int /*<<< orphan*/  TPS65217_PROTECT_NONE ; 
 int /*<<< orphan*/  TPS65217_REG_WLEDCTRL1 ; 
 int /*<<< orphan*/  TPS65217_WLEDCTRL1_FDIM_MASK ; 
 int /*<<< orphan*/  TPS65217_WLEDCTRL1_ISEL ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int tps65217_bl_disable (struct tps65217_bl*) ; 
 int tps65217_clear_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int tps65217_set_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int tps65217_bl_hw_init(struct tps65217_bl *tps65217_bl,
			struct tps65217_bl_pdata *pdata)
{
	int rc;

	rc = tps65217_bl_disable(tps65217_bl);
	if (rc)
		return rc;

	switch (pdata->isel) {
	case TPS65217_BL_ISET1:
		/* select ISET_1 current level */
		rc = tps65217_clear_bits(tps65217_bl->tps,
					TPS65217_REG_WLEDCTRL1,
					TPS65217_WLEDCTRL1_ISEL,
					TPS65217_PROTECT_NONE);
		if (rc) {
			dev_err(tps65217_bl->dev,
				"failed to select ISET1 current level: %d)\n",
				rc);
			return rc;
		}

		dev_dbg(tps65217_bl->dev, "selected ISET1 current level\n");

		break;

	case TPS65217_BL_ISET2:
		/* select ISET2 current level */
		rc = tps65217_set_bits(tps65217_bl->tps, TPS65217_REG_WLEDCTRL1,
				TPS65217_WLEDCTRL1_ISEL,
				TPS65217_WLEDCTRL1_ISEL, TPS65217_PROTECT_NONE);
		if (rc) {
			dev_err(tps65217_bl->dev,
				"failed to select ISET2 current level: %d\n",
				rc);
			return rc;
		}

		dev_dbg(tps65217_bl->dev, "selected ISET2 current level\n");

		break;

	default:
		dev_err(tps65217_bl->dev,
			"invalid value for current level: %d\n", pdata->isel);
		return -EINVAL;
	}

	/* set PWM frequency */
	rc = tps65217_set_bits(tps65217_bl->tps,
			TPS65217_REG_WLEDCTRL1,
			TPS65217_WLEDCTRL1_FDIM_MASK,
			pdata->fdim,
			TPS65217_PROTECT_NONE);
	if (rc) {
		dev_err(tps65217_bl->dev,
			"failed to select PWM dimming frequency: %d\n",
			rc);
		return rc;
	}

	return 0;
}
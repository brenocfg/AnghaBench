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
typedef  scalar_t__ u16 ;
struct TYPE_2__ {int /*<<< orphan*/  regmap; } ;
struct encx24j600_priv {TYPE_1__ ctx; } ;

/* Variables and functions */
 scalar_t__ CLKRDY ; 
 int EINVAL ; 
 int /*<<< orphan*/  ESTAT ; 
 int ETIMEDOUT ; 
 int /*<<< orphan*/  EUDAST ; 
 scalar_t__ EUDAST_TEST_VAL ; 
 int /*<<< orphan*/  SETETHRST ; 
 int /*<<< orphan*/  encx24j600_cmd (struct encx24j600_priv*,int /*<<< orphan*/ ) ; 
 scalar_t__ encx24j600_read_reg (struct encx24j600_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  encx24j600_write_reg (struct encx24j600_priv*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  regcache_cache_bypass (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static int encx24j600_soft_reset(struct encx24j600_priv *priv)
{
	int ret = 0;
	int timeout;
	u16 eudast;

	/* Write and verify a test value to EUDAST */
	regcache_cache_bypass(priv->ctx.regmap, true);
	timeout = 10;
	do {
		encx24j600_write_reg(priv, EUDAST, EUDAST_TEST_VAL);
		eudast = encx24j600_read_reg(priv, EUDAST);
		usleep_range(25, 100);
	} while ((eudast != EUDAST_TEST_VAL) && --timeout);
	regcache_cache_bypass(priv->ctx.regmap, false);

	if (timeout == 0) {
		ret = -ETIMEDOUT;
		goto err_out;
	}

	/* Wait for CLKRDY to become set */
	timeout = 10;
	while (!(encx24j600_read_reg(priv, ESTAT) & CLKRDY) && --timeout)
		usleep_range(25, 100);

	if (timeout == 0) {
		ret = -ETIMEDOUT;
		goto err_out;
	}

	/* Issue a System Reset command */
	encx24j600_cmd(priv, SETETHRST);
	usleep_range(25, 100);

	/* Confirm that EUDAST has 0000h after system reset */
	if (encx24j600_read_reg(priv, EUDAST) != 0) {
		ret = -EINVAL;
		goto err_out;
	}

	/* Wait for PHY register and status bits to become available */
	usleep_range(256, 1000);

err_out:
	return ret;
}
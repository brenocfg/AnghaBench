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
typedef  int u8 ;
struct i2c_client {int dummy; } ;
struct ef4_nic {int phy_mode; int /*<<< orphan*/  net_dev; } ;
struct TYPE_2__ {struct i2c_client* hwmon_client; struct i2c_client* ioexp_client; } ;

/* Variables and functions */
 int ETIMEDOUT ; 
 int /*<<< orphan*/  HZ ; 
 int /*<<< orphan*/  MAX664X_REG_RSL ; 
 int /*<<< orphan*/  P0_CONFIG ; 
 int P0_EN_1V0X_LBN ; 
 int P0_EN_1V2_LBN ; 
 int P0_EN_2V5_LBN ; 
 int P0_EN_3V3X_LBN ; 
 int P0_EN_5V_LBN ; 
 int /*<<< orphan*/  P0_OUT ; 
 int P0_X_TRST_LBN ; 
 int P1_AFE_PWD_LBN ; 
 int /*<<< orphan*/  P1_CONFIG ; 
 int /*<<< orphan*/  P1_IN ; 
 int P1_SPARE_LBN ; 
 int PHY_MODE_SPECIAL ; 
 TYPE_1__* falcon_board (struct ef4_nic*) ; 
 int /*<<< orphan*/  hw ; 
 int i2c_smbus_read_byte_data (struct i2c_client*,int /*<<< orphan*/ ) ; 
 int i2c_smbus_write_byte_data (struct i2c_client*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  netif_info (struct ef4_nic*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  schedule_timeout_uninterruptible (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sfe4001_poweroff (struct ef4_nic*) ; 

__attribute__((used)) static int sfe4001_poweron(struct ef4_nic *efx)
{
	struct i2c_client *ioexp_client = falcon_board(efx)->ioexp_client;
	struct i2c_client *hwmon_client = falcon_board(efx)->hwmon_client;
	unsigned int i, j;
	int rc;
	u8 out;

	/* Clear any previous over-temperature alert */
	rc = i2c_smbus_read_byte_data(hwmon_client, MAX664X_REG_RSL);
	if (rc < 0)
		return rc;

	/* Enable port 0 and port 1 outputs on IO expander */
	rc = i2c_smbus_write_byte_data(ioexp_client, P0_CONFIG, 0x00);
	if (rc)
		return rc;
	rc = i2c_smbus_write_byte_data(ioexp_client, P1_CONFIG,
				       0xff & ~(1 << P1_SPARE_LBN));
	if (rc)
		goto fail_on;

	/* If PHY power is on, turn it all off and wait 1 second to
	 * ensure a full reset.
	 */
	rc = i2c_smbus_read_byte_data(ioexp_client, P0_OUT);
	if (rc < 0)
		goto fail_on;
	out = 0xff & ~((0 << P0_EN_1V2_LBN) | (0 << P0_EN_2V5_LBN) |
		       (0 << P0_EN_3V3X_LBN) | (0 << P0_EN_5V_LBN) |
		       (0 << P0_EN_1V0X_LBN));
	if (rc != out) {
		netif_info(efx, hw, efx->net_dev, "power-cycling PHY\n");
		rc = i2c_smbus_write_byte_data(ioexp_client, P0_OUT, out);
		if (rc)
			goto fail_on;
		schedule_timeout_uninterruptible(HZ);
	}

	for (i = 0; i < 20; ++i) {
		/* Turn on 1.2V, 2.5V, 3.3V and 5V power rails */
		out = 0xff & ~((1 << P0_EN_1V2_LBN) | (1 << P0_EN_2V5_LBN) |
			       (1 << P0_EN_3V3X_LBN) | (1 << P0_EN_5V_LBN) |
			       (1 << P0_X_TRST_LBN));
		if (efx->phy_mode & PHY_MODE_SPECIAL)
			out |= 1 << P0_EN_3V3X_LBN;

		rc = i2c_smbus_write_byte_data(ioexp_client, P0_OUT, out);
		if (rc)
			goto fail_on;
		msleep(10);

		/* Turn on 1V power rail */
		out &= ~(1 << P0_EN_1V0X_LBN);
		rc = i2c_smbus_write_byte_data(ioexp_client, P0_OUT, out);
		if (rc)
			goto fail_on;

		netif_info(efx, hw, efx->net_dev,
			   "waiting for DSP boot (attempt %d)...\n", i);

		/* In flash config mode, DSP does not turn on AFE, so
		 * just wait 1 second.
		 */
		if (efx->phy_mode & PHY_MODE_SPECIAL) {
			schedule_timeout_uninterruptible(HZ);
			return 0;
		}

		for (j = 0; j < 10; ++j) {
			msleep(100);

			/* Check DSP has asserted AFE power line */
			rc = i2c_smbus_read_byte_data(ioexp_client, P1_IN);
			if (rc < 0)
				goto fail_on;
			if (rc & (1 << P1_AFE_PWD_LBN))
				return 0;
		}
	}

	netif_info(efx, hw, efx->net_dev, "timed out waiting for DSP boot\n");
	rc = -ETIMEDOUT;
fail_on:
	sfe4001_poweroff(efx);
	return rc;
}
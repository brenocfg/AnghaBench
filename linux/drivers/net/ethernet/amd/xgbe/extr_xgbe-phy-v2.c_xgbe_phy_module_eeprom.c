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
typedef  scalar_t__ u8 ;
struct xgbe_sfp_eeprom {int dummy; } ;
struct xgbe_prv_data {int /*<<< orphan*/  netdev; struct xgbe_phy_data* phy_data; } ;
struct xgbe_phy_data {scalar_t__ port_mode; scalar_t__ sfp_mod_absent; } ;
struct ethtool_eeprom {unsigned int len; int offset; } ;
typedef  int /*<<< orphan*/  eeprom_addr ;

/* Variables and functions */
 int EINVAL ; 
 int EIO ; 
 int ENXIO ; 
 scalar_t__ XGBE_PORT_MODE_SFP ; 
 scalar_t__ XGBE_SFP_DIAGS_SUPPORTED (struct xgbe_sfp_eeprom*) ; 
 int /*<<< orphan*/  XGBE_SFP_DIAG_INFO_ADDRESS ; 
 int XGBE_SFP_EEPROM_BASE_LEN ; 
 int XGBE_SFP_EEPROM_DIAG_LEN ; 
 int XGBE_SFP_EEPROM_MAX ; 
 int /*<<< orphan*/  XGBE_SFP_SERIAL_ID_ADDRESS ; 
 int /*<<< orphan*/  netdev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  netif_running (int /*<<< orphan*/ ) ; 
 int xgbe_phy_get_comm_ownership (struct xgbe_prv_data*) ; 
 int xgbe_phy_i2c_read (struct xgbe_prv_data*,int /*<<< orphan*/ ,scalar_t__*,int,scalar_t__*,int) ; 
 int /*<<< orphan*/  xgbe_phy_put_comm_ownership (struct xgbe_prv_data*) ; 
 int xgbe_phy_sfp_get_mux (struct xgbe_prv_data*) ; 
 int /*<<< orphan*/  xgbe_phy_sfp_put_mux (struct xgbe_prv_data*) ; 

__attribute__((used)) static int xgbe_phy_module_eeprom(struct xgbe_prv_data *pdata,
				  struct ethtool_eeprom *eeprom, u8 *data)
{
	struct xgbe_phy_data *phy_data = pdata->phy_data;
	u8 eeprom_addr, eeprom_data[XGBE_SFP_EEPROM_MAX];
	struct xgbe_sfp_eeprom *sfp_eeprom;
	unsigned int i, j, rem;
	int ret;

	rem = eeprom->len;

	if (!eeprom->len) {
		ret = -EINVAL;
		goto done;
	}

	if ((eeprom->offset + eeprom->len) > XGBE_SFP_EEPROM_MAX) {
		ret = -EINVAL;
		goto done;
	}

	if (phy_data->port_mode != XGBE_PORT_MODE_SFP) {
		ret = -ENXIO;
		goto done;
	}

	if (!netif_running(pdata->netdev)) {
		ret = -EIO;
		goto done;
	}

	if (phy_data->sfp_mod_absent) {
		ret = -EIO;
		goto done;
	}

	ret = xgbe_phy_get_comm_ownership(pdata);
	if (ret) {
		ret = -EIO;
		goto done;
	}

	ret = xgbe_phy_sfp_get_mux(pdata);
	if (ret) {
		netdev_err(pdata->netdev, "I2C error setting SFP MUX\n");
		ret = -EIO;
		goto put_own;
	}

	/* Read the SFP serial ID eeprom */
	eeprom_addr = 0;
	ret = xgbe_phy_i2c_read(pdata, XGBE_SFP_SERIAL_ID_ADDRESS,
				&eeprom_addr, sizeof(eeprom_addr),
				eeprom_data, XGBE_SFP_EEPROM_BASE_LEN);
	if (ret) {
		netdev_err(pdata->netdev,
			   "I2C error reading SFP EEPROM\n");
		ret = -EIO;
		goto put_mux;
	}

	sfp_eeprom = (struct xgbe_sfp_eeprom *)eeprom_data;

	if (XGBE_SFP_DIAGS_SUPPORTED(sfp_eeprom)) {
		/* Read the SFP diagnostic eeprom */
		eeprom_addr = 0;
		ret = xgbe_phy_i2c_read(pdata, XGBE_SFP_DIAG_INFO_ADDRESS,
					&eeprom_addr, sizeof(eeprom_addr),
					eeprom_data + XGBE_SFP_EEPROM_BASE_LEN,
					XGBE_SFP_EEPROM_DIAG_LEN);
		if (ret) {
			netdev_err(pdata->netdev,
				   "I2C error reading SFP DIAGS\n");
			ret = -EIO;
			goto put_mux;
		}
	}

	for (i = 0, j = eeprom->offset; i < eeprom->len; i++, j++) {
		if ((j >= XGBE_SFP_EEPROM_BASE_LEN) &&
		    !XGBE_SFP_DIAGS_SUPPORTED(sfp_eeprom))
			break;

		data[i] = eeprom_data[j];
		rem--;
	}

put_mux:
	xgbe_phy_sfp_put_mux(pdata);

put_own:
	xgbe_phy_put_comm_ownership(pdata);

done:
	eeprom->len -= rem;

	return ret;
}
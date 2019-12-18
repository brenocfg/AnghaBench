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
typedef  int /*<<< orphan*/  u8 ;
typedef  scalar_t__ u16 ;
struct net_device {int dummy; } ;
struct ethtool_eeprom {scalar_t__ offset; scalar_t__ len; } ;
struct bnxt {int dummy; } ;

/* Variables and functions */
 scalar_t__ ETH_MODULE_SFF_8436_LEN ; 
 int /*<<< orphan*/  I2C_DEV_ADDR_A0 ; 
 int /*<<< orphan*/  I2C_DEV_ADDR_A2 ; 
 int bnxt_read_sfp_module_eeprom_info (struct bnxt*,int /*<<< orphan*/ ,int,scalar_t__,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 
 struct bnxt* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int bnxt_get_module_eeprom(struct net_device *dev,
				  struct ethtool_eeprom *eeprom,
				  u8 *data)
{
	struct bnxt *bp = netdev_priv(dev);
	u16  start = eeprom->offset, length = eeprom->len;
	int rc = 0;

	memset(data, 0, eeprom->len);

	/* Read A0 portion of the EEPROM */
	if (start < ETH_MODULE_SFF_8436_LEN) {
		if (start + eeprom->len > ETH_MODULE_SFF_8436_LEN)
			length = ETH_MODULE_SFF_8436_LEN - start;
		rc = bnxt_read_sfp_module_eeprom_info(bp, I2C_DEV_ADDR_A0, 0,
						      start, length, data);
		if (rc)
			return rc;
		start += length;
		data += length;
		length = eeprom->len - length;
	}

	/* Read A2 portion of the EEPROM */
	if (length) {
		start -= ETH_MODULE_SFF_8436_LEN;
		rc = bnxt_read_sfp_module_eeprom_info(bp, I2C_DEV_ADDR_A2, 1,
						      start, length, data);
	}
	return rc;
}
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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u64 ;
typedef  scalar_t__ u32 ;
struct s2io_nic {TYPE_1__* pdev; } ;
struct net_device {int dummy; } ;
struct ethtool_eeprom {int magic; scalar_t__ offset; scalar_t__ len; } ;
struct TYPE_2__ {int vendor; int device; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG_PRINT (int /*<<< orphan*/ ,char*) ; 
 int EFAULT ; 
 int /*<<< orphan*/  ERR_DBG ; 
 scalar_t__ INV (int /*<<< orphan*/ ) ; 
 scalar_t__ XENA_EEPROM_SPACE ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,scalar_t__*,int) ; 
 struct s2io_nic* netdev_priv (struct net_device*) ; 
 scalar_t__ read_eeprom (struct s2io_nic*,scalar_t__,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int s2io_ethtool_geeprom(struct net_device *dev,
				struct ethtool_eeprom *eeprom, u8 * data_buf)
{
	u32 i, valid;
	u64 data;
	struct s2io_nic *sp = netdev_priv(dev);

	eeprom->magic = sp->pdev->vendor | (sp->pdev->device << 16);

	if ((eeprom->offset + eeprom->len) > (XENA_EEPROM_SPACE))
		eeprom->len = XENA_EEPROM_SPACE - eeprom->offset;

	for (i = 0; i < eeprom->len; i += 4) {
		if (read_eeprom(sp, (eeprom->offset + i), &data)) {
			DBG_PRINT(ERR_DBG, "Read of EEPROM failed\n");
			return -EFAULT;
		}
		valid = INV(data);
		memcpy((data_buf + i), &valid, 4);
	}
	return 0;
}
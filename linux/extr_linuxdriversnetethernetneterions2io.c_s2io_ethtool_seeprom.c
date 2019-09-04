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
typedef  scalar_t__ u8 ;
typedef  int u64 ;
typedef  int u32 ;
struct s2io_nic {TYPE_1__* pdev; } ;
struct net_device {int dummy; } ;
struct ethtool_eeprom {int len; int magic; scalar_t__ offset; } ;
struct TYPE_2__ {int vendor; int device; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG_PRINT (int /*<<< orphan*/ ,char*,...) ; 
 int EFAULT ; 
 int /*<<< orphan*/  ERR_DBG ; 
 struct s2io_nic* netdev_priv (struct net_device*) ; 
 scalar_t__ write_eeprom (struct s2io_nic*,scalar_t__,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int s2io_ethtool_seeprom(struct net_device *dev,
				struct ethtool_eeprom *eeprom,
				u8 *data_buf)
{
	int len = eeprom->len, cnt = 0;
	u64 valid = 0, data;
	struct s2io_nic *sp = netdev_priv(dev);

	if (eeprom->magic != (sp->pdev->vendor | (sp->pdev->device << 16))) {
		DBG_PRINT(ERR_DBG,
			  "ETHTOOL_WRITE_EEPROM Err: "
			  "Magic value is wrong, it is 0x%x should be 0x%x\n",
			  (sp->pdev->vendor | (sp->pdev->device << 16)),
			  eeprom->magic);
		return -EFAULT;
	}

	while (len) {
		data = (u32)data_buf[cnt] & 0x000000FF;
		if (data)
			valid = (u32)(data << 24);
		else
			valid = data;

		if (write_eeprom(sp, (eeprom->offset + cnt), valid, 0)) {
			DBG_PRINT(ERR_DBG,
				  "ETHTOOL_WRITE_EEPROM Err: "
				  "Cannot write into the specified offset\n");
			return -EFAULT;
		}
		cnt++;
		len--;
	}

	return 0;
}
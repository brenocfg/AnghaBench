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
struct octeon_device {int /*<<< orphan*/  boardinfo; TYPE_1__* pci_dev; } ;
struct octeon_board_info {char* name; char* serial_number; int /*<<< orphan*/  minor; int /*<<< orphan*/  major; } ;
struct net_device {int dummy; } ;
struct lio {struct octeon_device* oct_dev; } ;
struct ethtool_eeprom {int /*<<< orphan*/  magic; scalar_t__ offset; } ;
struct TYPE_2__ {int /*<<< orphan*/  vendor; } ;

/* Variables and functions */
 int EINVAL ; 
 struct lio* GET_LIO (struct net_device*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
lio_get_eeprom(struct net_device *netdev, struct ethtool_eeprom *eeprom,
	       u8 *bytes)
{
	struct lio *lio = GET_LIO(netdev);
	struct octeon_device *oct_dev = lio->oct_dev;
	struct octeon_board_info *board_info;

	if (eeprom->offset)
		return -EINVAL;

	eeprom->magic = oct_dev->pci_dev->vendor;
	board_info = (struct octeon_board_info *)(&oct_dev->boardinfo);
	sprintf((char *)bytes,
		"boardname:%s serialnum:%s maj:%lld min:%lld\n",
		board_info->name, board_info->serial_number,
		board_info->major, board_info->minor);

	return 0;
}
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
struct octeon_device {int /*<<< orphan*/  boardinfo; } ;
struct octeon_board_info {char* name; char* serial_number; int /*<<< orphan*/  minor; int /*<<< orphan*/  major; } ;
struct net_device {int dummy; } ;
struct lio {struct octeon_device* oct_dev; } ;

/* Variables and functions */
 struct lio* GET_LIO (struct net_device*) ; 
 int sprintf (int /*<<< orphan*/ *,char*,char*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int lio_get_eeprom_len(struct net_device *netdev)
{
	u8 buf[192];
	struct lio *lio = GET_LIO(netdev);
	struct octeon_device *oct_dev = lio->oct_dev;
	struct octeon_board_info *board_info;
	int len;

	board_info = (struct octeon_board_info *)(&oct_dev->boardinfo);
	len = sprintf(buf, "boardname:%s serialnum:%s maj:%lld min:%lld\n",
		      board_info->name, board_info->serial_number,
		      board_info->major, board_info->minor);

	return len;
}
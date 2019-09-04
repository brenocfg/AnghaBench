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
typedef  char u8 ;
struct ipack_device {char* id; char id_vendor; char id_device; int speed_8mhz; int speed_32mhz; int id_crc_correct; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*,char,char) ; 
 char ipack_calc_crc1 (struct ipack_device*) ; 

__attribute__((used)) static void ipack_parse_id1(struct ipack_device *dev)
{
	u8 *id = dev->id;
	u8 crc;

	dev->id_vendor = id[4];
	dev->id_device = id[5];
	dev->speed_8mhz = 1;
	dev->speed_32mhz = (id[7] == 'H');
	crc = ipack_calc_crc1(dev);
	dev->id_crc_correct = (crc == id[11]);
	if (!dev->id_crc_correct) {
		dev_warn(&dev->dev, "ID CRC invalid found 0x%x, expected 0x%x.\n",
				id[11], crc);
	}
}
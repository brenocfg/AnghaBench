#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int addr; } ;
struct saa7134_dev {scalar_t__ board; int /*<<< orphan*/  name; TYPE_1__ i2c_client; } ;

/* Variables and functions */
 scalar_t__ SAA7134_BOARD_MD7134 ; 
 int i2c_master_recv (TYPE_1__*,unsigned char*,int) ; 
 int i2c_master_send (TYPE_1__*,unsigned char*,int) ; 
 int /*<<< orphan*/  pr_info (char*,int,int,...) ; 
 int /*<<< orphan*/  pr_warn (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  saa7134_i2c_eeprom_md7134_gate (struct saa7134_dev*) ; 

__attribute__((used)) static int
saa7134_i2c_eeprom(struct saa7134_dev *dev, unsigned char *eedata, int len)
{
	unsigned char buf;
	int i,err;

	if (dev->board == SAA7134_BOARD_MD7134)
		saa7134_i2c_eeprom_md7134_gate(dev);

	dev->i2c_client.addr = 0xa0 >> 1;
	buf = 0;
	if (1 != (err = i2c_master_send(&dev->i2c_client,&buf,1))) {
		pr_info("%s: Huh, no eeprom present (err=%d)?\n",
		       dev->name,err);
		return -1;
	}
	if (len != (err = i2c_master_recv(&dev->i2c_client,eedata,len))) {
		pr_warn("%s: i2c eeprom read error (err=%d)\n",
		       dev->name,err);
		return -1;
	}

	for (i = 0; i < len; i += 16) {
		int size = (len - i) > 16 ? 16 : len - i;

		pr_info("i2c eeprom %02x: %*ph\n", i, size, &eedata[i]);
	}

	return 0;
}
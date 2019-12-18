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
typedef  int u8 ;
struct saa7146_dev {int dummy; } ;
struct budget {int /*<<< orphan*/  i2c_adap; struct saa7146_dev* dev; } ;
struct budget_av {struct budget budget; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  SAA7146_GPIO_OUTHI ; 
 int /*<<< orphan*/  dprintk (int,char*,...) ; 
 int /*<<< orphan*/  i2c_readreg (int /*<<< orphan*/ *,int,int) ; 
 int i2c_writereg (int /*<<< orphan*/ *,int,int const,int const) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int* saa7113_tab ; 
 int /*<<< orphan*/  saa7146_setgpio (struct saa7146_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int saa7113_init(struct budget_av *budget_av)
{
	struct budget *budget = &budget_av->budget;
	struct saa7146_dev *saa = budget->dev;
	const u8 *data = saa7113_tab;

	saa7146_setgpio(saa, 0, SAA7146_GPIO_OUTHI);
	msleep(200);

	if (i2c_writereg(&budget->i2c_adap, 0x4a, 0x01, 0x08) != 1) {
		dprintk(1, "saa7113 not found on KNC card\n");
		return -ENODEV;
	}

	dprintk(1, "saa7113 detected and initializing\n");

	while (*data != 0xff) {
		i2c_writereg(&budget->i2c_adap, 0x4a, *data, *(data + 1));
		data += 2;
	}

	dprintk(1, "saa7113  status=%02x\n", i2c_readreg(&budget->i2c_adap, 0x4a, 0x1f));

	return 0;
}
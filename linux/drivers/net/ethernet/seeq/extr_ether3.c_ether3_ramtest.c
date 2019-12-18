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
struct net_device {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int RX_END ; 
 int /*<<< orphan*/  RX_LEN ; 
 int RX_START ; 
 int /*<<< orphan*/  TX_END ; 
 int /*<<< orphan*/  buffer_read ; 
 int /*<<< orphan*/  buffer_write ; 
 int /*<<< orphan*/  ether3_readbuffer (struct net_device*,unsigned char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ether3_setbuffer (struct net_device*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ether3_writebuffer (struct net_device*,unsigned char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (unsigned char*) ; 
 unsigned char* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (unsigned char*,unsigned char,int) ; 
 int /*<<< orphan*/  printk (char*,...) ; 

__attribute__((used)) static int
ether3_ramtest(struct net_device *dev, unsigned char byte)
{
	unsigned char *buffer = kmalloc(RX_END, GFP_KERNEL);
	int i,ret = 0;
	int max_errors = 4;
	int bad = -1;

	if (!buffer)
		return 1;

	memset(buffer, byte, RX_END);
	ether3_setbuffer(dev, buffer_write, 0);
	ether3_writebuffer(dev, buffer, TX_END);
	ether3_setbuffer(dev, buffer_write, RX_START);
	ether3_writebuffer(dev, buffer + RX_START, RX_LEN);
	memset(buffer, byte ^ 0xff, RX_END);
	ether3_setbuffer(dev, buffer_read, 0);
	ether3_readbuffer(dev, buffer, TX_END);
	ether3_setbuffer(dev, buffer_read, RX_START);
	ether3_readbuffer(dev, buffer + RX_START, RX_LEN);

	for (i = 0; i < RX_END; i++) {
		if (buffer[i] != byte) {
			if (max_errors > 0 && bad != buffer[i]) {
				printk("%s: RAM failed with (%02X instead of %02X) at 0x%04X",
				       dev->name, buffer[i], byte, i);
				ret = 2;
				max_errors--;
				bad = i;
			}
		} else {
			if (bad != -1) {
				if (bad != i - 1)
					printk(" - 0x%04X\n", i - 1);
				printk("\n");
				bad = -1;
			}
		}
	}
	if (bad != -1)
		printk(" - 0xffff\n");
	kfree(buffer);

	return ret;
}
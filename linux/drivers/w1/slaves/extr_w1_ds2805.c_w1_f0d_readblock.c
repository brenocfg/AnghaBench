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
typedef  int /*<<< orphan*/  wrbuf ;
typedef  char u8 ;
struct w1_slave {int /*<<< orphan*/  dev; int /*<<< orphan*/  master; } ;

/* Variables and functions */
 char W1_F0D_READ_EEPROM ; 
 int W1_F0D_READ_MAXLEN ; 
 int W1_F0D_READ_RETRIES ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  memcmp (char*,char*,int) ; 
 int /*<<< orphan*/  w1_read_block (int /*<<< orphan*/ ,char*,int) ; 
 scalar_t__ w1_reset_select_slave (struct w1_slave*) ; 
 int /*<<< orphan*/  w1_write_block (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static int w1_f0d_readblock(struct w1_slave *sl, int off, int count, char *buf)
{
	u8 wrbuf[3];
	u8 cmp[W1_F0D_READ_MAXLEN];
	int tries = W1_F0D_READ_RETRIES;

	do {
		wrbuf[0] = W1_F0D_READ_EEPROM;
		wrbuf[1] = off & 0x7f;
		wrbuf[2] = 0;

		if (w1_reset_select_slave(sl))
			return -1;

		w1_write_block(sl->master, wrbuf, sizeof(wrbuf));
		w1_read_block(sl->master, buf, count);

		if (w1_reset_select_slave(sl))
			return -1;

		w1_write_block(sl->master, wrbuf, sizeof(wrbuf));
		w1_read_block(sl->master, cmp, count);

		if (!memcmp(cmp, buf, count))
			return 0;
	} while (--tries);

	dev_err(&sl->dev, "proof reading failed %d times\n",
			W1_F0D_READ_RETRIES);

	return -1;
}
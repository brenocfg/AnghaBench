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
typedef  int u8 ;
struct sp2 {TYPE_1__* client; } ;
struct dvb_ca_en50221 {struct sp2* data; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int SP2_MOD_CTL_RST ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int sp2_write_i2c (struct sp2*,int,int*,int) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

int sp2_ci_slot_reset(struct dvb_ca_en50221 *en50221, int slot)
{
	struct sp2 *s = en50221->data;
	u8 buf;
	int ret;

	dev_dbg(&s->client->dev, "slot: %d\n", slot);

	if (slot != 0)
		return -EINVAL;

	/* RST on */
	buf = SP2_MOD_CTL_RST;
	ret = sp2_write_i2c(s, 0x00, &buf, 1);

	if (ret)
		return ret;

	usleep_range(500, 600);

	/* RST off */
	buf = 0x00;
	ret = sp2_write_i2c(s, 0x00, &buf, 1);

	if (ret)
		return ret;

	msleep(1000);

	return 0;
}
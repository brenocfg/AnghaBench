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
 int SP2_MOD_CTL_TSIEN ; 
 int SP2_MOD_CTL_TSOEN ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  sp2_read_i2c (struct sp2*,int,int*,int) ; 
 int sp2_write_i2c (struct sp2*,int /*<<< orphan*/ ,int*,int) ; 

int sp2_ci_slot_ts_enable(struct dvb_ca_en50221 *en50221, int slot)
{
	struct sp2 *s = en50221->data;
	u8 buf;

	dev_dbg(&s->client->dev, "slot:%d\n", slot);

	if (slot != 0)
		return -EINVAL;

	sp2_read_i2c(s, 0x00, &buf, 1);

	/* disable bypass and enable TS */
	buf |= (SP2_MOD_CTL_TSOEN | SP2_MOD_CTL_TSIEN);
	return sp2_write_i2c(s, 0, &buf, 1);
}
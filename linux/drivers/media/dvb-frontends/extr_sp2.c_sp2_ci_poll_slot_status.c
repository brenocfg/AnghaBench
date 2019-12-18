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
struct sp2 {int status; scalar_t__ next_status_checked_time; TYPE_1__* client; } ;
struct dvb_ca_en50221 {struct sp2* data; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int DVB_CA_EN50221_POLL_CAM_PRESENT ; 
 int DVB_CA_EN50221_POLL_CAM_READY ; 
 int SP2_MOD_CTL_DET ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int,int) ; 
 scalar_t__ jiffies ; 
 scalar_t__ msecs_to_jiffies (int) ; 
 int sp2_read_i2c (struct sp2*,int,int*,int) ; 
 scalar_t__ time_after (scalar_t__,scalar_t__) ; 

int sp2_ci_poll_slot_status(struct dvb_ca_en50221 *en50221,
				int slot, int open)
{
	struct sp2 *s = en50221->data;
	u8 buf[2];
	int ret;

	dev_dbg(&s->client->dev, "slot:%d open:%d\n", slot, open);

	/*
	 * CAM module INSERT/REMOVE processing. Slow operation because of i2c
	 * transfers. Throttle read to one per sec.
	 */
	if (time_after(jiffies, s->next_status_checked_time)) {
		ret = sp2_read_i2c(s, 0x00, buf, 1);
		s->next_status_checked_time = jiffies +	msecs_to_jiffies(1000);

		if (ret)
			return 0;

		if (buf[0] & SP2_MOD_CTL_DET)
			s->status = DVB_CA_EN50221_POLL_CAM_PRESENT |
					DVB_CA_EN50221_POLL_CAM_READY;
		else
			s->status = 0;
	}

	return s->status;
}
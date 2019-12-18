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
typedef  int u8 ;
struct zet6223_ts {int fingernum; void* max_y; void* max_x; TYPE_1__* client; } ;
typedef  int /*<<< orphan*/  cmd ;
typedef  int /*<<< orphan*/  buf ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EIO ; 
 int ZET6223_CMD_INFO ; 
 int ZET6223_CMD_INFO_LENGTH ; 
 int ZET6223_MAX_FINGERS ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*,int,int) ; 
 void* get_unaligned_le16 (int*) ; 
 int i2c_master_recv (TYPE_1__*,int*,int) ; 
 int i2c_master_send (TYPE_1__*,int*,int) ; 

__attribute__((used)) static int zet6223_query_device(struct zet6223_ts *ts)
{
	u8 buf[ZET6223_CMD_INFO_LENGTH];
	u8 cmd = ZET6223_CMD_INFO;
	int ret;
	int error;

	ret = i2c_master_send(ts->client, &cmd, sizeof(cmd));
	if (ret != sizeof(cmd)) {
		error = ret < 0 ? ret : -EIO;
		dev_err(&ts->client->dev,
			"touchpanel info cmd failed: %d\n", error);
		return error;
	}

	ret = i2c_master_recv(ts->client, buf, sizeof(buf));
	if (ret != sizeof(buf)) {
		error = ret < 0 ? ret : -EIO;
		dev_err(&ts->client->dev,
			"failed to retrieve touchpanel info: %d\n", error);
		return error;
	}

	ts->fingernum = buf[15] & 0x7F;
	if (ts->fingernum > ZET6223_MAX_FINGERS) {
		dev_warn(&ts->client->dev,
			 "touchpanel reports %d fingers, limiting to %d\n",
			 ts->fingernum, ZET6223_MAX_FINGERS);
		ts->fingernum = ZET6223_MAX_FINGERS;
	}

	ts->max_x = get_unaligned_le16(&buf[8]);
	ts->max_y = get_unaligned_le16(&buf[10]);

	return 0;
}
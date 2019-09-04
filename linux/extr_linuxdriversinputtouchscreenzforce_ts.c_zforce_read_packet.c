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
struct zforce_ts {int /*<<< orphan*/  access_mutex; struct i2c_client* client; } ;
struct i2c_client {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EIO ; 
 int FRAME_START ; 
 size_t PAYLOAD_BODY ; 
 size_t PAYLOAD_HEADER ; 
 size_t PAYLOAD_LENGTH ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int,int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int i2c_master_recv (struct i2c_client*,int*,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int zforce_read_packet(struct zforce_ts *ts, u8 *buf)
{
	struct i2c_client *client = ts->client;
	int ret;

	mutex_lock(&ts->access_mutex);

	/* read 2 byte message header */
	ret = i2c_master_recv(client, buf, 2);
	if (ret < 0) {
		dev_err(&client->dev, "error reading header: %d\n", ret);
		goto unlock;
	}

	if (buf[PAYLOAD_HEADER] != FRAME_START) {
		dev_err(&client->dev, "invalid frame start: %d\n", buf[0]);
		ret = -EIO;
		goto unlock;
	}

	if (buf[PAYLOAD_LENGTH] == 0) {
		dev_err(&client->dev, "invalid payload length: %d\n",
			buf[PAYLOAD_LENGTH]);
		ret = -EIO;
		goto unlock;
	}

	/* read the message */
	ret = i2c_master_recv(client, &buf[PAYLOAD_BODY], buf[PAYLOAD_LENGTH]);
	if (ret < 0) {
		dev_err(&client->dev, "error reading payload: %d\n", ret);
		goto unlock;
	}

	dev_dbg(&client->dev, "read %d bytes for response command 0x%x\n",
		buf[PAYLOAD_LENGTH], buf[PAYLOAD_BODY]);

unlock:
	mutex_unlock(&ts->access_mutex);
	return ret;
}
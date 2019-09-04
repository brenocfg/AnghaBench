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
typedef  int /*<<< orphan*/  u8 ;
struct goodix_ts_data {int id; int /*<<< orphan*/  version; TYPE_1__* client; } ;
typedef  int /*<<< orphan*/  buf ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  GOODIX_REG_ID ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_unaligned_le16 (int /*<<< orphan*/ *) ; 
 int goodix_i2c_read (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 scalar_t__ kstrtou16 (char*,int,int*) ; 
 int /*<<< orphan*/  memcpy (char*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int goodix_read_version(struct goodix_ts_data *ts)
{
	int error;
	u8 buf[6];
	char id_str[5];

	error = goodix_i2c_read(ts->client, GOODIX_REG_ID, buf, sizeof(buf));
	if (error) {
		dev_err(&ts->client->dev, "read version failed: %d\n", error);
		return error;
	}

	memcpy(id_str, buf, 4);
	id_str[4] = 0;
	if (kstrtou16(id_str, 10, &ts->id))
		ts->id = 0x1001;

	ts->version = get_unaligned_le16(&buf[4]);

	dev_info(&ts->client->dev, "ID %d, version: %04x\n", ts->id,
		 ts->version);

	return 0;
}
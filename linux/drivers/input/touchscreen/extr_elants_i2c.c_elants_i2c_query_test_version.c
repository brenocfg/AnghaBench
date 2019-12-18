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
typedef  int u16 ;
struct i2c_client {int /*<<< orphan*/  dev; } ;
struct elants_data {int test_version; int solution_version; struct i2c_client* client; } ;
typedef  int /*<<< orphan*/  resp ;
typedef  int /*<<< orphan*/  cmd ;

/* Variables and functions */
 int CMD_HEADER_READ ; 
 int EINVAL ; 
 int E_ELAN_INFO_TEST_VER ; 
 int HEADER_SIZE ; 
 int MAX_RETRIES ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int,int,int*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int elants_i2c_execute_command (struct i2c_client*,int const*,int,int*,int) ; 
 int elants_i2c_parse_version (int*) ; 

__attribute__((used)) static int elants_i2c_query_test_version(struct elants_data *ts)
{
	struct i2c_client *client = ts->client;
	int error, retry_cnt;
	u16 version;
	const u8 cmd[] = { CMD_HEADER_READ, E_ELAN_INFO_TEST_VER, 0x00, 0x01 };
	u8 resp[HEADER_SIZE];

	for (retry_cnt = 0; retry_cnt < MAX_RETRIES; retry_cnt++) {
		error = elants_i2c_execute_command(client, cmd, sizeof(cmd),
						   resp, sizeof(resp));
		if (!error) {
			version = elants_i2c_parse_version(resp);
			ts->test_version = version >> 8;
			ts->solution_version = version & 0xff;

			return 0;
		}

		dev_dbg(&client->dev,
			"read test version error rc=%d, buf=%*phC\n",
			error, (int)sizeof(resp), resp);
	}

	dev_err(&client->dev, "Failed to read test version\n");

	return -EINVAL;
}
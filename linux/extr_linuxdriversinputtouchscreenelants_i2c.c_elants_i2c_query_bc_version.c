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
struct elants_data {int bc_version; int iap_version; struct i2c_client* client; } ;
typedef  int /*<<< orphan*/  resp ;
typedef  int /*<<< orphan*/  cmd ;

/* Variables and functions */
 int CMD_HEADER_READ ; 
 int E_ELAN_INFO_BC_VER ; 
 int HEADER_SIZE ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int,int,int*) ; 
 int elants_i2c_execute_command (struct i2c_client*,int const*,int,int*,int) ; 
 int elants_i2c_parse_version (int*) ; 

__attribute__((used)) static int elants_i2c_query_bc_version(struct elants_data *ts)
{
	struct i2c_client *client = ts->client;
	const u8 cmd[] = { CMD_HEADER_READ, E_ELAN_INFO_BC_VER, 0x00, 0x01 };
	u8 resp[HEADER_SIZE];
	u16 version;
	int error;

	error = elants_i2c_execute_command(client, cmd, sizeof(cmd),
					   resp, sizeof(resp));
	if (error) {
		dev_err(&client->dev,
			"read BC version error=%d, buf=%*phC\n",
			error, (int)sizeof(resp), resp);
		return error;
	}

	version = elants_i2c_parse_version(resp);
	ts->bc_version = version >> 8;
	ts->iap_version = version & 0xff;

	return 0;
}
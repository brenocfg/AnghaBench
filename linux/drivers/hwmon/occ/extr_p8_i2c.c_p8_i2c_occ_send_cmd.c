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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u16 ;
struct p8_i2c_occ {struct i2c_client* client; } ;
struct occ_response {int return_status; int /*<<< orphan*/  data_length; } ;
struct occ {struct occ_response resp; } ;
struct i2c_client {int dummy; } ;

/* Variables and functions */
 int EALREADY ; 
 int EINVAL ; 
 int EMSGSIZE ; 
 int EPROTO ; 
 int EREMOTEIO ; 
 int ETIMEDOUT ; 
 int /*<<< orphan*/  OCB_ADDR ; 
 int /*<<< orphan*/  OCB_DATA1 ; 
 int /*<<< orphan*/  OCB_DATA3 ; 
 int /*<<< orphan*/  OCC_CMD_IN_PRG_WAIT_MS ; 
 int /*<<< orphan*/  OCC_DATA_ATTN ; 
#define  OCC_RESP_BAD_STATE 140 
#define  OCC_RESP_CHKSUM_ERR 139 
#define  OCC_RESP_CMD_INVAL 138 
#define  OCC_RESP_CMD_IN_PRG 137 
#define  OCC_RESP_CMD_LEN_INVAL 136 
#define  OCC_RESP_CRIT_EXCEPT 135 
#define  OCC_RESP_CRIT_HW 134 
#define  OCC_RESP_CRIT_INIT 133 
#define  OCC_RESP_CRIT_OCB 132 
#define  OCC_RESP_CRIT_WATCHDOG 131 
 int OCC_RESP_DATA_BYTES ; 
#define  OCC_RESP_DATA_INVAL 130 
#define  OCC_RESP_INT_ERR 129 
#define  OCC_RESP_SUCCESS 128 
 int /*<<< orphan*/  OCC_SRAM_ADDR_CMD ; 
 int /*<<< orphan*/  OCC_SRAM_ADDR_RESP ; 
 int /*<<< orphan*/  OCC_TIMEOUT_MS ; 
 int /*<<< orphan*/  TASK_INTERRUPTIBLE ; 
 int get_unaligned_be16 (int /*<<< orphan*/ *) ; 
 unsigned long jiffies ; 
 void* msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 int p8_i2c_occ_getscom (struct i2c_client*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int p8_i2c_occ_putscom_be (struct i2c_client*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int p8_i2c_occ_putscom_u32 (struct i2c_client*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  schedule_timeout (long const) ; 
 int /*<<< orphan*/  set_current_state (int /*<<< orphan*/ ) ; 
 scalar_t__ time_after (unsigned long,unsigned long) ; 
 struct p8_i2c_occ* to_p8_i2c_occ (struct occ*) ; 

__attribute__((used)) static int p8_i2c_occ_send_cmd(struct occ *occ, u8 *cmd)
{
	int i, rc;
	unsigned long start;
	u16 data_length;
	const unsigned long timeout = msecs_to_jiffies(OCC_TIMEOUT_MS);
	const long wait_time = msecs_to_jiffies(OCC_CMD_IN_PRG_WAIT_MS);
	struct p8_i2c_occ *ctx = to_p8_i2c_occ(occ);
	struct i2c_client *client = ctx->client;
	struct occ_response *resp = &occ->resp;

	start = jiffies;

	/* set sram address for command */
	rc = p8_i2c_occ_putscom_u32(client, OCB_ADDR, OCC_SRAM_ADDR_CMD, 0);
	if (rc)
		return rc;

	/* write command (expected to already be BE), we need bus-endian... */
	rc = p8_i2c_occ_putscom_be(client, OCB_DATA3, cmd);
	if (rc)
		return rc;

	/* trigger OCC attention */
	rc = p8_i2c_occ_putscom_u32(client, OCB_DATA1, OCC_DATA_ATTN, 0);
	if (rc)
		return rc;

	do {
		/* set sram address for response */
		rc = p8_i2c_occ_putscom_u32(client, OCB_ADDR,
					    OCC_SRAM_ADDR_RESP, 0);
		if (rc)
			return rc;

		rc = p8_i2c_occ_getscom(client, OCB_DATA3, (u8 *)resp);
		if (rc)
			return rc;

		/* wait for OCC */
		if (resp->return_status == OCC_RESP_CMD_IN_PRG) {
			rc = -EALREADY;

			if (time_after(jiffies, start + timeout))
				break;

			set_current_state(TASK_INTERRUPTIBLE);
			schedule_timeout(wait_time);
		}
	} while (rc);

	/* check the OCC response */
	switch (resp->return_status) {
	case OCC_RESP_CMD_IN_PRG:
		rc = -ETIMEDOUT;
		break;
	case OCC_RESP_SUCCESS:
		rc = 0;
		break;
	case OCC_RESP_CMD_INVAL:
	case OCC_RESP_CMD_LEN_INVAL:
	case OCC_RESP_DATA_INVAL:
	case OCC_RESP_CHKSUM_ERR:
		rc = -EINVAL;
		break;
	case OCC_RESP_INT_ERR:
	case OCC_RESP_BAD_STATE:
	case OCC_RESP_CRIT_EXCEPT:
	case OCC_RESP_CRIT_INIT:
	case OCC_RESP_CRIT_WATCHDOG:
	case OCC_RESP_CRIT_OCB:
	case OCC_RESP_CRIT_HW:
		rc = -EREMOTEIO;
		break;
	default:
		rc = -EPROTO;
	}

	if (rc < 0)
		return rc;

	data_length = get_unaligned_be16(&resp->data_length);
	if (data_length > OCC_RESP_DATA_BYTES)
		return -EMSGSIZE;

	/* fetch the rest of the response data */
	for (i = 8; i < data_length + 7; i += 8) {
		rc = p8_i2c_occ_getscom(client, OCB_DATA3, ((u8 *)resp) + i);
		if (rc)
			return rc;
	}

	return 0;
}
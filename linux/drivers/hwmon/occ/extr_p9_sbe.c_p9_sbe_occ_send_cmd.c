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
struct p9_sbe_occ {int /*<<< orphan*/  sbe; } ;
struct occ_response {int return_status; } ;
struct occ {struct occ_response resp; } ;

/* Variables and functions */
 int EINVAL ; 
 int EPROTO ; 
 int EREMOTEIO ; 
 int ETIMEDOUT ; 
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
#define  OCC_RESP_DATA_INVAL 130 
#define  OCC_RESP_INT_ERR 129 
#define  OCC_RESP_SUCCESS 128 
 int fsi_occ_submit (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,struct occ_response*,size_t*) ; 
 struct p9_sbe_occ* to_p9_sbe_occ (struct occ*) ; 

__attribute__((used)) static int p9_sbe_occ_send_cmd(struct occ *occ, u8 *cmd)
{
	struct occ_response *resp = &occ->resp;
	struct p9_sbe_occ *ctx = to_p9_sbe_occ(occ);
	size_t resp_len = sizeof(*resp);
	int rc;

	rc = fsi_occ_submit(ctx->sbe, cmd, 8, resp, &resp_len);
	if (rc < 0)
		return rc;

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

	return rc;
}
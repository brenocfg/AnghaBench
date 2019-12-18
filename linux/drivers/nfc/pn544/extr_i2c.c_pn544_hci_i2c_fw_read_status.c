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
struct pn544_i2c_phy {struct i2c_client* i2c_dev; } ;
struct pn544_i2c_fw_frame_response {int status; } ;
struct i2c_client {int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  response ;

/* Variables and functions */
 int EACCES ; 
 int EBADMSG ; 
 int EINVAL ; 
 int EIO ; 
 int ENODATA ; 
 int ENOKEY ; 
 int ENOMEM ; 
 int ENOTSUPP ; 
 int EPROTO ; 
 int ETIMEDOUT ; 
#define  PN544_FW_CMD_RESULT_ACCESS_DENIED 141 
#define  PN544_FW_CMD_RESULT_BAD_CRC 140 
#define  PN544_FW_CMD_RESULT_CHUNK_ERROR 139 
#define  PN544_FW_CMD_RESULT_CHUNK_OK 138 
#define  PN544_FW_CMD_RESULT_COMMAND_REJECTED 137 
#define  PN544_FW_CMD_RESULT_CRYPTOGRAPHIC_ERROR 136 
#define  PN544_FW_CMD_RESULT_INVALID_LENGTH 135 
#define  PN544_FW_CMD_RESULT_INVALID_PARAMETER 134 
#define  PN544_FW_CMD_RESULT_MEMORY_ERROR 133 
#define  PN544_FW_CMD_RESULT_PROTOCOL_ERROR 132 
#define  PN544_FW_CMD_RESULT_TIMEOUT 131 
#define  PN544_FW_CMD_RESULT_UNSUPPORTED_COMMAND 130 
#define  PN544_FW_CMD_RESULT_VERSION_CONDITIONS_ERROR 129 
#define  PN544_FW_CMD_RESULT_WRITE_FAILED 128 
 int i2c_master_recv (struct i2c_client*,char*,int) ; 
 int /*<<< orphan*/  nfc_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static int pn544_hci_i2c_fw_read_status(struct pn544_i2c_phy *phy)
{
	int r;
	struct pn544_i2c_fw_frame_response response;
	struct i2c_client *client = phy->i2c_dev;

	r = i2c_master_recv(client, (char *) &response, sizeof(response));
	if (r != sizeof(response)) {
		nfc_err(&client->dev, "cannot read fw status\n");
		return -EIO;
	}

	usleep_range(3000, 6000);

	switch (response.status) {
	case 0:
		return 0;
	case PN544_FW_CMD_RESULT_CHUNK_OK:
		return response.status;
	case PN544_FW_CMD_RESULT_TIMEOUT:
		return -ETIMEDOUT;
	case PN544_FW_CMD_RESULT_BAD_CRC:
		return -ENODATA;
	case PN544_FW_CMD_RESULT_ACCESS_DENIED:
		return -EACCES;
	case PN544_FW_CMD_RESULT_PROTOCOL_ERROR:
		return -EPROTO;
	case PN544_FW_CMD_RESULT_INVALID_PARAMETER:
		return -EINVAL;
	case PN544_FW_CMD_RESULT_UNSUPPORTED_COMMAND:
		return -ENOTSUPP;
	case PN544_FW_CMD_RESULT_INVALID_LENGTH:
		return -EBADMSG;
	case PN544_FW_CMD_RESULT_CRYPTOGRAPHIC_ERROR:
		return -ENOKEY;
	case PN544_FW_CMD_RESULT_VERSION_CONDITIONS_ERROR:
		return -EINVAL;
	case PN544_FW_CMD_RESULT_MEMORY_ERROR:
		return -ENOMEM;
	case PN544_FW_CMD_RESULT_COMMAND_REJECTED:
		return -EACCES;
	case PN544_FW_CMD_RESULT_WRITE_FAILED:
	case PN544_FW_CMD_RESULT_CHUNK_ERROR:
		return -EIO;
	default:
		return -EIO;
	}
}
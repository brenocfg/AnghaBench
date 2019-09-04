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
struct si476x_core {scalar_t__ revision; TYPE_1__* client; } ;
typedef  int /*<<< orphan*/  buffer ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
 int EIO ; 
#define  SI476X_ERR_BAD_ARG1 137 
#define  SI476X_ERR_BAD_ARG2 136 
#define  SI476X_ERR_BAD_ARG3 135 
#define  SI476X_ERR_BAD_ARG4 134 
#define  SI476X_ERR_BAD_BOOT_MODE 133 
#define  SI476X_ERR_BAD_COMMAND 132 
#define  SI476X_ERR_BAD_INTERNAL_MEMORY 131 
#define  SI476X_ERR_BAD_PATCH 130 
#define  SI476X_ERR_BAD_PROPERTY 129 
#define  SI476X_ERR_BUSY 128 
 int /*<<< orphan*/  SI476X_I2C_RECV ; 
 scalar_t__ SI476X_REVISION_A10 ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,...) ; 
 int si476x_core_i2c_xfer (struct si476x_core*,int /*<<< orphan*/ ,int*,int) ; 

__attribute__((used)) static int si476x_core_parse_and_nag_about_error(struct si476x_core *core)
{
	int err;
	char *cause;
	u8 buffer[2];

	if (core->revision != SI476X_REVISION_A10) {
		err = si476x_core_i2c_xfer(core, SI476X_I2C_RECV,
					   buffer, sizeof(buffer));
		if (err == sizeof(buffer)) {
			switch (buffer[1]) {
			case SI476X_ERR_BAD_COMMAND:
				cause = "Bad command";
				err = -EINVAL;
				break;
			case SI476X_ERR_BAD_ARG1:
				cause = "Bad argument #1";
				err = -EINVAL;
				break;
			case SI476X_ERR_BAD_ARG2:
				cause = "Bad argument #2";
				err = -EINVAL;
				break;
			case SI476X_ERR_BAD_ARG3:
				cause = "Bad argument #3";
				err = -EINVAL;
				break;
			case SI476X_ERR_BAD_ARG4:
				cause = "Bad argument #4";
				err = -EINVAL;
				break;
			case SI476X_ERR_BUSY:
				cause = "Chip is busy";
				err = -EBUSY;
				break;
			case SI476X_ERR_BAD_INTERNAL_MEMORY:
				cause = "Bad internal memory";
				err = -EIO;
				break;
			case SI476X_ERR_BAD_PATCH:
				cause = "Bad patch";
				err = -EINVAL;
				break;
			case SI476X_ERR_BAD_BOOT_MODE:
				cause = "Bad boot mode";
				err = -EINVAL;
				break;
			case SI476X_ERR_BAD_PROPERTY:
				cause = "Bad property";
				err = -EINVAL;
				break;
			default:
				cause = "Unknown";
				err = -EIO;
			}

			dev_err(&core->client->dev,
				"[Chip error status]: %s\n", cause);
		} else {
			dev_err(&core->client->dev,
				"Failed to fetch error code\n");
			err = (err >= 0) ? -EIO : err;
		}
	} else {
		err = -EIO;
	}

	return err;
}
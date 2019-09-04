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
struct smscore_device_t {int /*<<< orphan*/  devpath; } ;
typedef  enum sms_device_type_st { ____Placeholder_sms_device_type_st } sms_device_type_st ;
struct TYPE_2__ {char** fw; } ;

/* Variables and functions */
 int DEVICE_MODE_MAX ; 
 int DEVICE_MODE_NONE ; 
 int SMS_NUM_OF_DEVICE_TYPES ; 
 int SMS_UNKNOWN_TYPE ; 
 int /*<<< orphan*/  pr_debug (char*,int,int) ; 
 TYPE_1__* sms_get_board (int) ; 
 char*** smscore_fw_lkup ; 
 int smscore_get_board_id (struct smscore_device_t*) ; 
 int smscore_registry_gettype (int /*<<< orphan*/ ) ; 

__attribute__((used)) static char *smscore_get_fw_filename(struct smscore_device_t *coredev,
			      int mode)
{
	char **fw;
	int board_id = smscore_get_board_id(coredev);
	enum sms_device_type_st type;

	type = smscore_registry_gettype(coredev->devpath);

	/* Prevent looking outside the smscore_fw_lkup table */
	if (type <= SMS_UNKNOWN_TYPE || type >= SMS_NUM_OF_DEVICE_TYPES)
		return NULL;
	if (mode <= DEVICE_MODE_NONE || mode >= DEVICE_MODE_MAX)
		return NULL;

	pr_debug("trying to get fw name from sms_boards board_id %d mode %d\n",
		  board_id, mode);
	fw = sms_get_board(board_id)->fw;
	if (!fw || !fw[mode]) {
		pr_debug("cannot find fw name in sms_boards, getting from lookup table mode %d type %d\n",
			  mode, type);
		return smscore_fw_lkup[type][mode];
	}

	return fw[mode];
}
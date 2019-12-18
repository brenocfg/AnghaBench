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
typedef  void* u8 ;
struct gm12u320_device {void** cmd_buf; int /*<<< orphan*/  udev; } ;

/* Variables and functions */
 int CMD_SIZE ; 
 int /*<<< orphan*/  CMD_TIMEOUT ; 
 int /*<<< orphan*/  DATA_TIMEOUT ; 
 int EIO ; 
 int /*<<< orphan*/  GM12U320_ERR (char*,int) ; 
 int /*<<< orphan*/  MISC_RCV_EPT ; 
 int /*<<< orphan*/  MISC_SND_EPT ; 
 int MISC_VALUE_SIZE ; 
 int READ_STATUS_SIZE ; 
 int /*<<< orphan*/  cmd_misc ; 
 int /*<<< orphan*/  memcpy (void**,int /*<<< orphan*/ *,int) ; 
 int usb_bulk_msg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void**,int,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_rcvbulkpipe (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_sndbulkpipe (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int gm12u320_misc_request(struct gm12u320_device *gm12u320,
				 u8 req_a, u8 req_b,
				 u8 arg_a, u8 arg_b, u8 arg_c, u8 arg_d)
{
	int ret, len;

	memcpy(gm12u320->cmd_buf, &cmd_misc, CMD_SIZE);
	gm12u320->cmd_buf[20] = req_a;
	gm12u320->cmd_buf[21] = req_b;
	gm12u320->cmd_buf[22] = arg_a;
	gm12u320->cmd_buf[23] = arg_b;
	gm12u320->cmd_buf[24] = arg_c;
	gm12u320->cmd_buf[25] = arg_d;

	/* Send request */
	ret = usb_bulk_msg(gm12u320->udev,
			   usb_sndbulkpipe(gm12u320->udev, MISC_SND_EPT),
			   gm12u320->cmd_buf, CMD_SIZE, &len, CMD_TIMEOUT);
	if (ret || len != CMD_SIZE) {
		GM12U320_ERR("Misc. req. error %d\n", ret);
		return -EIO;
	}

	/* Read value */
	ret = usb_bulk_msg(gm12u320->udev,
			   usb_rcvbulkpipe(gm12u320->udev, MISC_RCV_EPT),
			   gm12u320->cmd_buf, MISC_VALUE_SIZE, &len,
			   DATA_TIMEOUT);
	if (ret || len != MISC_VALUE_SIZE) {
		GM12U320_ERR("Misc. value error %d\n", ret);
		return -EIO;
	}
	/* cmd_buf[0] now contains the read value, which we don't use */

	/* Read status */
	ret = usb_bulk_msg(gm12u320->udev,
			   usb_rcvbulkpipe(gm12u320->udev, MISC_RCV_EPT),
			   gm12u320->cmd_buf, READ_STATUS_SIZE, &len,
			   CMD_TIMEOUT);
	if (ret || len != READ_STATUS_SIZE) {
		GM12U320_ERR("Misc. status error %d\n", ret);
		return -EIO;
	}

	return 0;
}
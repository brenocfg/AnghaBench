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

/* Variables and functions */

void smsendian_handle_tx_message(void *buffer)
{
#ifdef __BIG_ENDIAN
	struct sms_msg_data *msg = (struct sms_msg_data *)buffer;
	int i;
	int msg_words;

	switch (msg->x_msg_header.msg_type) {
	case MSG_SMS_DATA_DOWNLOAD_REQ:
	{
		msg->msg_data[0] = le32_to_cpu((__force __le32)(msg->msg_data[0]));
		break;
	}

	default:
		msg_words = (msg->x_msg_header.msg_length -
				sizeof(struct sms_msg_hdr))/4;

		for (i = 0; i < msg_words; i++)
			msg->msg_data[i] = le32_to_cpu((__force __le32)msg->msg_data[i]);

		break;
	}
#endif /* __BIG_ENDIAN */
}
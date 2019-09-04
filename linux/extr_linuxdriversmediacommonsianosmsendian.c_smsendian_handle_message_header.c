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

void smsendian_handle_message_header(void *msg)
{
#ifdef __BIG_ENDIAN
	struct sms_msg_hdr *phdr = (struct sms_msg_hdr *)msg;

	phdr->msg_type = le16_to_cpu((__force __le16)phdr->msg_type);
	phdr->msg_length = le16_to_cpu((__force __le16)phdr->msg_length);
	phdr->msg_flags = le16_to_cpu((__force __le16)phdr->msg_flags);
#endif /* __BIG_ENDIAN */
}
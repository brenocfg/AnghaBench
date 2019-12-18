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
typedef  int u32 ;
typedef  int u16 ;
struct cdn_dp_device {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int cdn_dp_mailbox_read (struct cdn_dp_device*) ; 

__attribute__((used)) static int cdn_dp_mailbox_validate_receive(struct cdn_dp_device *dp,
					   u8 module_id, u8 opcode,
					   u16 req_size)
{
	u32 mbox_size, i;
	u8 header[4];
	int ret;

	/* read the header of the message */
	for (i = 0; i < 4; i++) {
		ret = cdn_dp_mailbox_read(dp);
		if (ret < 0)
			return ret;

		header[i] = ret;
	}

	mbox_size = (header[2] << 8) | header[3];

	if (opcode != header[0] || module_id != header[1] ||
	    req_size != mbox_size) {
		/*
		 * If the message in mailbox is not what we want, we need to
		 * clear the mailbox by reading its contents.
		 */
		for (i = 0; i < mbox_size; i++)
			if (cdn_dp_mailbox_read(dp) < 0)
				break;

		return -EINVAL;
	}

	return 0;
}
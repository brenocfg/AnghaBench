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
struct ican3_msg {int* data; void* len; void* spec; } ;
struct ican3_dev {int dummy; } ;
typedef  int /*<<< orphan*/  msg ;

/* Variables and functions */
 void* MSG_SETAFILMASK ; 
 void* SETAFILMASK_FASTIF ; 
 void* SETAFILMASK_REJECT ; 
 void* cpu_to_le16 (int) ; 
 int ican3_send_msg (struct ican3_dev*,struct ican3_msg*) ; 
 int /*<<< orphan*/  memset (struct ican3_msg*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int ican3_set_id_filter(struct ican3_dev *mod, bool accept)
{
	struct ican3_msg msg;
	int ret;

	/* Standard Frame Format */
	memset(&msg, 0, sizeof(msg));
	msg.spec = MSG_SETAFILMASK;
	msg.len = cpu_to_le16(5);
	msg.data[0] = 0x00; /* IDLo LSB */
	msg.data[1] = 0x00; /* IDLo MSB */
	msg.data[2] = 0xff; /* IDHi LSB */
	msg.data[3] = 0x07; /* IDHi MSB */

	/* accept all frames for fast host if, or reject all frames */
	msg.data[4] = accept ? SETAFILMASK_FASTIF : SETAFILMASK_REJECT;

	ret = ican3_send_msg(mod, &msg);
	if (ret)
		return ret;

	/* Extended Frame Format */
	memset(&msg, 0, sizeof(msg));
	msg.spec = MSG_SETAFILMASK;
	msg.len = cpu_to_le16(13);
	msg.data[0] = 0;    /* MUX = 0 */
	msg.data[1] = 0x00; /* IDLo LSB */
	msg.data[2] = 0x00;
	msg.data[3] = 0x00;
	msg.data[4] = 0x20; /* IDLo MSB */
	msg.data[5] = 0xff; /* IDHi LSB */
	msg.data[6] = 0xff;
	msg.data[7] = 0xff;
	msg.data[8] = 0x3f; /* IDHi MSB */

	/* accept all frames for fast host if, or reject all frames */
	msg.data[9] = accept ? SETAFILMASK_FASTIF : SETAFILMASK_REJECT;

	return ican3_send_msg(mod, &msg);
}
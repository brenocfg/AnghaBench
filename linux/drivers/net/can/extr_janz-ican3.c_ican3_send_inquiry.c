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
struct ican3_msg {int* data; int /*<<< orphan*/  len; int /*<<< orphan*/  spec; } ;
struct ican3_dev {int dummy; } ;
typedef  int /*<<< orphan*/  msg ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_INQUIRY ; 
 int /*<<< orphan*/  cpu_to_le16 (int) ; 
 int ican3_send_msg (struct ican3_dev*,struct ican3_msg*) ; 
 int /*<<< orphan*/  memset (struct ican3_msg*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int ican3_send_inquiry(struct ican3_dev *mod, u8 subspec)
{
	struct ican3_msg msg;

	memset(&msg, 0, sizeof(msg));
	msg.spec = MSG_INQUIRY;
	msg.len = cpu_to_le16(2);
	msg.data[0] = subspec;
	msg.data[1] = 0x00;

	return ican3_send_msg(mod, &msg);
}
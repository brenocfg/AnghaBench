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
struct firedtv {int dummy; } ;
struct ca_msg {int* msg; } ;

/* Variables and functions */
 int avc_ca_pmt (struct firedtv*,int*,int) ; 

__attribute__((used)) static int fdtv_ca_pmt(struct firedtv *fdtv, void *arg)
{
	struct ca_msg *msg = arg;
	int data_pos;
	int data_length;
	int i;

	data_pos = 4;
	if (msg->msg[3] & 0x80) {
		data_length = 0;
		for (i = 0; i < (msg->msg[3] & 0x7f); i++)
			data_length = (data_length << 8) + msg->msg[data_pos++];
	} else {
		data_length = msg->msg[3];
	}

	return avc_ca_pmt(fdtv, &msg->msg[data_pos], data_length);
}
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
struct ishtp_cl_data {int /*<<< orphan*/  multi_packet_cnt; int /*<<< orphan*/  bad_recv_cnt; } ;
struct ishtp_cl {int dummy; } ;
struct TYPE_2__ {int command; } ;
struct hostif_msg {TYPE_1__ hdr; } ;

/* Variables and functions */
 int CMD_MASK ; 
 int /*<<< orphan*/  cl_data_to_dev (struct ishtp_cl_data*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ,unsigned int,unsigned char,unsigned char,unsigned char,unsigned char,unsigned int,int /*<<< orphan*/ ,int) ; 
 struct ishtp_cl_data* ishtp_get_client_data (struct ishtp_cl*) ; 

__attribute__((used)) static void report_bad_packet(struct ishtp_cl *hid_ishtp_cl, void *recv_buf,
			      size_t cur_pos,  size_t payload_len)
{
	struct hostif_msg *recv_msg = recv_buf;
	struct ishtp_cl_data *client_data = ishtp_get_client_data(hid_ishtp_cl);

	dev_err(cl_data_to_dev(client_data), "[hid-ish]: BAD packet %02X\n"
		"total_bad=%u cur_pos=%u\n"
		"[%02X %02X %02X %02X]\n"
		"payload_len=%u\n"
		"multi_packet_cnt=%u\n"
		"is_response=%02X\n",
		recv_msg->hdr.command, client_data->bad_recv_cnt,
		(unsigned int)cur_pos,
		((unsigned char *)recv_msg)[0], ((unsigned char *)recv_msg)[1],
		((unsigned char *)recv_msg)[2], ((unsigned char *)recv_msg)[3],
		(unsigned int)payload_len, client_data->multi_packet_cnt,
		recv_msg->hdr.command & ~CMD_MASK);
}
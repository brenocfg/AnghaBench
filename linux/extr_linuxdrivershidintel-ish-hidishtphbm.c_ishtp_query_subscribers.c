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
struct ishtp_msg_hdr {int dummy; } ;
struct ishtp_device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  cmd; } ;
struct ish_system_states_query_subscribers {TYPE_1__ hdr; } ;

/* Variables and functions */
 int /*<<< orphan*/  ISHTP_SYSTEM_STATE_CLIENT_ADDR ; 
 int /*<<< orphan*/  SYSTEM_STATE_QUERY_SUBSCRIBERS ; 
 int /*<<< orphan*/  fix_cl_hdr (struct ishtp_msg_hdr*,size_t const,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ishtp_write_message (struct ishtp_device*,struct ishtp_msg_hdr*,unsigned char*) ; 
 int /*<<< orphan*/  memset (struct ish_system_states_query_subscribers*,int /*<<< orphan*/ ,size_t const) ; 

void ishtp_query_subscribers(struct ishtp_device *dev)
{
	struct ishtp_msg_hdr	ishtp_hdr;
	struct ish_system_states_query_subscribers query_subscribers_msg;
	const size_t len = sizeof(struct ish_system_states_query_subscribers);

	fix_cl_hdr(&ishtp_hdr, len, ISHTP_SYSTEM_STATE_CLIENT_ADDR);

	memset(&query_subscribers_msg, 0, len);
	query_subscribers_msg.hdr.cmd = SYSTEM_STATE_QUERY_SUBSCRIBERS;

	ishtp_write_message(dev, &ishtp_hdr,
		(unsigned char *)&query_subscribers_msg);
}
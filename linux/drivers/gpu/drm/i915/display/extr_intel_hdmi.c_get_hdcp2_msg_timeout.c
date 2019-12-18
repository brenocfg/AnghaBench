#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u8 ;
struct TYPE_3__ {scalar_t__ msg_id; int timeout; int timeout2; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_1__*) ; 
 int EINVAL ; 
 scalar_t__ HDCP_2_2_AKE_SEND_HPRIME ; 
 TYPE_1__* hdcp2_msg_data ; 

__attribute__((used)) static int get_hdcp2_msg_timeout(u8 msg_id, bool is_paired)
{
	int i;

	for (i = 0; i < ARRAY_SIZE(hdcp2_msg_data); i++)
		if (hdcp2_msg_data[i].msg_id == msg_id &&
		    (msg_id != HDCP_2_2_AKE_SEND_HPRIME || is_paired))
			return hdcp2_msg_data[i].timeout;
		else if (hdcp2_msg_data[i].msg_id == msg_id)
			return hdcp2_msg_data[i].timeout2;

	return -EINVAL;
}
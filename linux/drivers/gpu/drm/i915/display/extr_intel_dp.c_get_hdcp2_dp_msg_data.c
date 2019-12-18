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
typedef  scalar_t__ u8 ;
struct hdcp2_dp_msg_data {scalar_t__ msg_id; } ;

/* Variables and functions */
 int ARRAY_SIZE (struct hdcp2_dp_msg_data const*) ; 
 struct hdcp2_dp_msg_data const* hdcp2_dp_msg_data ; 

__attribute__((used)) static const struct hdcp2_dp_msg_data *get_hdcp2_dp_msg_data(u8 msg_id)
{
	int i;

	for (i = 0; i < ARRAY_SIZE(hdcp2_dp_msg_data); i++)
		if (hdcp2_dp_msg_data[i].msg_id == msg_id)
			return &hdcp2_dp_msg_data[i];

	return NULL;
}
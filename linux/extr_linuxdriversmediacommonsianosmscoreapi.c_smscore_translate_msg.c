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
typedef  enum msg_types { ____Placeholder_msg_types } msg_types ;

/* Variables and functions */
 int ARRAY_SIZE (char**) ; 
 int MSG_TYPE_BASE_VAL ; 
 char** siano_msgs ; 

char *smscore_translate_msg(enum msg_types msgtype)
{
	int i = msgtype - MSG_TYPE_BASE_VAL;
	char *msg;

	if (i < 0 || i >= ARRAY_SIZE(siano_msgs))
		return "Unknown msg type";

	msg = siano_msgs[i];

	if (!*msg)
		return "Unknown msg type";

	return msg;
}
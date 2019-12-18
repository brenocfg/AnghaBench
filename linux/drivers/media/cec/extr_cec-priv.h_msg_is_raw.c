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
struct cec_msg {int flags; } ;

/* Variables and functions */
 int CEC_MSG_FL_RAW ; 

__attribute__((used)) static inline bool msg_is_raw(const struct cec_msg *msg)
{
	return msg->flags & CEC_MSG_FL_RAW;
}
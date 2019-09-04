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
typedef  int u64 ;
struct hfi1_devdata {int dummy; } ;

/* Variables and functions */
 int IDLE_MSG_TYPE_SHIFT ; 
 int IDLE_PAYLOAD_MASK ; 
 int IDLE_PAYLOAD_SHIFT ; 
 scalar_t__ IDLE_SMA ; 
 int send_idle_message (struct hfi1_devdata*,int) ; 

int send_idle_sma(struct hfi1_devdata *dd, u64 message)
{
	u64 data;

	data = ((message & IDLE_PAYLOAD_MASK) << IDLE_PAYLOAD_SHIFT) |
		((u64)IDLE_SMA << IDLE_MSG_TYPE_SHIFT);
	return send_idle_message(dd, data);
}
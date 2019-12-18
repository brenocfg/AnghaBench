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
typedef  int /*<<< orphan*/  u32 ;
struct ivtv {int dummy; } ;

/* Variables and functions */
 int EBUSY ; 
 int ivtv_api_call (struct ivtv*,int,int,int /*<<< orphan*/ *) ; 

int ivtv_api(struct ivtv *itv, int cmd, int args, u32 data[])
{
	int res = ivtv_api_call(itv, cmd, args, data);

	/* Allow a single retry, probably already too late though.
	   If there is no free mailbox then that is usually an indication
	   of a more serious problem. */
	return (res == -EBUSY) ? ivtv_api_call(itv, cmd, args, data) : res;
}
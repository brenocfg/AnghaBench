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
struct bnxt {int dummy; } ;

/* Variables and functions */
 int bnxt_hwrm_do_send_msg (struct bnxt*,void*,int /*<<< orphan*/ ,int,int) ; 

int _hwrm_send_message_silent(struct bnxt *bp, void *msg, u32 msg_len,
			      int timeout)
{
	return bnxt_hwrm_do_send_msg(bp, msg, msg_len, timeout, true);
}
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
struct bnxt {int /*<<< orphan*/  hwrm_cmd_lock; } ;

/* Variables and functions */
 int _hwrm_send_message (struct bnxt*,void*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

int hwrm_send_message(struct bnxt *bp, void *msg, u32 msg_len, int timeout)
{
	int rc;

	mutex_lock(&bp->hwrm_cmd_lock);
	rc = _hwrm_send_message(bp, msg, msg_len, timeout);
	mutex_unlock(&bp->hwrm_cmd_lock);
	return rc;
}
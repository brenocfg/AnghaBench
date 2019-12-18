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
struct nfp_nsp {int /*<<< orphan*/  cpp; } ;

/* Variables and functions */
 int EAGAIN ; 
 int ERESTARTSYS ; 
 int ETIMEDOUT ; 
 unsigned long HZ ; 
 unsigned long NFP_NSP_TIMEOUT_BOOT ; 
 int /*<<< orphan*/  SPCODE_NOOP ; 
 unsigned long jiffies ; 
 scalar_t__ msleep_interruptible (int) ; 
 int /*<<< orphan*/  nfp_dbg (int /*<<< orphan*/ ,char*,unsigned long) ; 
 int /*<<< orphan*/  nfp_err (int /*<<< orphan*/ ,char*,int) ; 
 int nfp_nsp_command (struct nfp_nsp*,int /*<<< orphan*/ ) ; 
 scalar_t__ time_after (unsigned long const,unsigned long const) ; 

int nfp_nsp_wait(struct nfp_nsp *state)
{
	const unsigned long wait_until = jiffies + NFP_NSP_TIMEOUT_BOOT * HZ;
	int err;

	nfp_dbg(state->cpp, "Waiting for NSP to respond (%u sec max).\n",
		NFP_NSP_TIMEOUT_BOOT);

	for (;;) {
		const unsigned long start_time = jiffies;

		err = nfp_nsp_command(state, SPCODE_NOOP);
		if (err != -EAGAIN)
			break;

		if (msleep_interruptible(25)) {
			err = -ERESTARTSYS;
			break;
		}

		if (time_after(start_time, wait_until)) {
			err = -ETIMEDOUT;
			break;
		}
	}
	if (err)
		nfp_err(state->cpp, "NSP failed to respond %d\n", err);

	return err;
}
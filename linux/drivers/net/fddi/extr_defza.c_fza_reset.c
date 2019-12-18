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
typedef  scalar_t__ uint ;
struct fza_private {scalar_t__ state_chg_flag; int /*<<< orphan*/  name; TYPE_1__* regs; int /*<<< orphan*/  state_chg_wait; int /*<<< orphan*/  lock; } ;
struct TYPE_2__ {int /*<<< orphan*/  status; } ;

/* Variables and functions */
 int EIO ; 
 scalar_t__ FZA_STATE_UNINITIALIZED ; 
 scalar_t__ FZA_STATUS_GET_STATE (scalar_t__) ; 
 int /*<<< orphan*/  FZA_STATUS_GET_TEST (scalar_t__) ; 
 int HZ ; 
 int /*<<< orphan*/  fza_do_reset (struct fza_private*) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ,scalar_t__,...) ; 
 int /*<<< orphan*/  pr_info (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ readw_u (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 long wait_event_timeout (int /*<<< orphan*/ ,scalar_t__,int) ; 

__attribute__((used)) static int fza_reset(struct fza_private *fp)
{
	unsigned long flags;
	uint status, state;
	long t;

	pr_info("%s: resetting the board...\n", fp->name);

	spin_lock_irqsave(&fp->lock, flags);
	fp->state_chg_flag = 0;
	fza_do_reset(fp);
	spin_unlock_irqrestore(&fp->lock, flags);

	/* DEC says RESET needs up to 30 seconds to complete.  My DEFZA-AA
	 * rev. C03 happily finishes in 9.7 seconds. :-)  But we need to
	 * be on the safe side...
	 */
	t = wait_event_timeout(fp->state_chg_wait, fp->state_chg_flag,
			       45 * HZ);
	status = readw_u(&fp->regs->status);
	state = FZA_STATUS_GET_STATE(status);
	if (fp->state_chg_flag == 0) {
		pr_err("%s: RESET timed out!, state %x\n", fp->name, state);
		return -EIO;
	}
	if (state != FZA_STATE_UNINITIALIZED) {
		pr_err("%s: RESET failed!, state %x, failure ID %x\n",
		       fp->name, state, FZA_STATUS_GET_TEST(status));
		return -EIO;
	}
	pr_info("%s: OK\n", fp->name);
	pr_debug("%s: RESET: %lums elapsed\n", fp->name,
		 (45 * HZ - t) * 1000 / HZ);

	return 0;
}
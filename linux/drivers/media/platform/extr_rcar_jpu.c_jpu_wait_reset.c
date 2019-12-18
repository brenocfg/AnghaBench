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
struct jpu {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ETIMEDOUT ; 
 int /*<<< orphan*/  JCCMD ; 
 int JCCMD_SRST ; 
 int /*<<< orphan*/  JPU_RESET_TIMEOUT ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 unsigned long jiffies ; 
 int jpu_read (struct jpu*,int /*<<< orphan*/ ) ; 
 unsigned long msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  schedule () ; 
 scalar_t__ time_after (unsigned long,unsigned long) ; 

__attribute__((used)) static int jpu_wait_reset(struct jpu *jpu)
{
	unsigned long timeout;

	timeout = jiffies + msecs_to_jiffies(JPU_RESET_TIMEOUT);

	while (jpu_read(jpu, JCCMD) & JCCMD_SRST) {
		if (time_after(jiffies, timeout)) {
			dev_err(jpu->dev, "timed out in reset\n");
			return -ETIMEDOUT;
		}
		schedule();
	}

	return 0;
}
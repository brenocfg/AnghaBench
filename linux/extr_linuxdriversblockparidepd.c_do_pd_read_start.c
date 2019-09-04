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
typedef  enum action { ____Placeholder_action } action ;

/* Variables and functions */
 int Fail ; 
 int Hold ; 
 int /*<<< orphan*/  IDE_READ ; 
 scalar_t__ PD_MAX_RETRIES ; 
 scalar_t__ PD_TMO ; 
 int STAT_ERR ; 
 int /*<<< orphan*/  STAT_READY ; 
 int Wait ; 
 int /*<<< orphan*/  do_pd_read_drq ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  pd_block ; 
 int /*<<< orphan*/  pd_current ; 
 int /*<<< orphan*/  pd_ide_command (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ pd_retries ; 
 int /*<<< orphan*/  pd_run ; 
 scalar_t__ pd_timeout ; 
 int pd_wait_for (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  phase ; 

__attribute__((used)) static enum action do_pd_read_start(void)
{
	if (pd_wait_for(pd_current, STAT_READY, "do_pd_read") & STAT_ERR) {
		if (pd_retries < PD_MAX_RETRIES) {
			pd_retries++;
			return Wait;
		}
		return Fail;
	}
	pd_ide_command(pd_current, IDE_READ, pd_block, pd_run);
	phase = do_pd_read_drq;
	pd_timeout = jiffies + PD_TMO;
	return Hold;
}
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
 int Ok ; 
 scalar_t__ PD_MAX_RETRIES ; 
 int STAT_ERR ; 
 int /*<<< orphan*/  STAT_READY ; 
 int Wait ; 
 int /*<<< orphan*/  do_pd_write_start ; 
 int /*<<< orphan*/  jiffies ; 
 int /*<<< orphan*/  pd_current ; 
 int /*<<< orphan*/  pd_ready () ; 
 scalar_t__ pd_retries ; 
 int /*<<< orphan*/  pd_timeout ; 
 int pd_wait_for (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  phase ; 
 int /*<<< orphan*/  time_after_eq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static enum action do_pd_write_done(void)
{
	if (!pd_ready() && !time_after_eq(jiffies, pd_timeout))
		return Hold;

	if (pd_wait_for(pd_current, STAT_READY, "do_pd_write_done") & STAT_ERR) {
		if (pd_retries < PD_MAX_RETRIES) {
			pd_retries++;
			phase = do_pd_write_start;
			return Wait;
		}
		return Fail;
	}
	return Ok;
}
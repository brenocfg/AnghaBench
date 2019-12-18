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

/* Variables and functions */
 unsigned long HZ ; 
 int /*<<< orphan*/  cec_work ; 
 int /*<<< orphan*/  mod_delayed_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  round_jiffies (unsigned long) ; 
 int /*<<< orphan*/  system_wq ; 

__attribute__((used)) static void cec_mod_work(unsigned long interval)
{
	unsigned long iv;

	iv = interval * HZ;
	mod_delayed_work(system_wq, &cec_work, round_jiffies(iv));
}
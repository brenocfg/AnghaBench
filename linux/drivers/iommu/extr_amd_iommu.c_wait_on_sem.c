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
typedef  scalar_t__ u64 ;

/* Variables and functions */
 int EIO ; 
 int LOOP_TIMEOUT ; 
 int /*<<< orphan*/  pr_alert (char*) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int wait_on_sem(volatile u64 *sem)
{
	int i = 0;

	while (*sem == 0 && i < LOOP_TIMEOUT) {
		udelay(1);
		i += 1;
	}

	if (i == LOOP_TIMEOUT) {
		pr_alert("Completion-Wait loop timed out\n");
		return -EIO;
	}

	return 0;
}
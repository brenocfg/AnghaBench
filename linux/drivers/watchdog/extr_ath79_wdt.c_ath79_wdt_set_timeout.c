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
 int EINVAL ; 
 int /*<<< orphan*/  ath79_wdt_keepalive () ; 
 int max_timeout ; 
 int timeout ; 

__attribute__((used)) static int ath79_wdt_set_timeout(int val)
{
	if (val < 1 || val > max_timeout)
		return -EINVAL;

	timeout = val;
	ath79_wdt_keepalive();

	return 0;
}
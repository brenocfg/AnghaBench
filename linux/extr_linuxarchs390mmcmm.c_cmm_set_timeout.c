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
 int /*<<< orphan*/  cmm_set_timer () ; 
 long cmm_timeout_pages ; 
 long cmm_timeout_seconds ; 

__attribute__((used)) static void cmm_set_timeout(long nr, long seconds)
{
	cmm_timeout_pages = nr;
	cmm_timeout_seconds = seconds;
	cmm_set_timer();
}
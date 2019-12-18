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
struct TYPE_2__ {int /*<<< orphan*/  timer; } ;

/* Variables and functions */
 scalar_t__ WDT_TIMEOUT ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  pikawdt_keepalive () ; 
 TYPE_1__ pikawdt_private ; 

__attribute__((used)) static void pikawdt_start(void)
{
	pikawdt_keepalive();
	mod_timer(&pikawdt_private.timer, jiffies + WDT_TIMEOUT);
}
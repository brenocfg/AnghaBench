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
typedef  scalar_t__ u16 ;
struct ieee80211_device {int dummy; } ;
struct ba_record {int valid; int /*<<< orphan*/  timer; } ;

/* Variables and functions */
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ msecs_to_jiffies (scalar_t__) ; 

__attribute__((used)) static void ActivateBAEntry(struct ieee80211_device *ieee, struct ba_record *pBA, u16 Time)
{
	pBA->valid = true;
	if (Time != 0)
		mod_timer(&pBA->timer, jiffies + msecs_to_jiffies(Time));
}
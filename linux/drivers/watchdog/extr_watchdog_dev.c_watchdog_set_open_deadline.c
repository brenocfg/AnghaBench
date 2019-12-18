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
struct watchdog_core_data {scalar_t__ open_deadline; } ;

/* Variables and functions */
 scalar_t__ KTIME_MAX ; 
 scalar_t__ ktime_get () ; 
 scalar_t__ ktime_set (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ open_timeout ; 

__attribute__((used)) static void watchdog_set_open_deadline(struct watchdog_core_data *data)
{
	data->open_deadline = open_timeout ?
		ktime_get() + ktime_set(open_timeout, 0) : KTIME_MAX;
}
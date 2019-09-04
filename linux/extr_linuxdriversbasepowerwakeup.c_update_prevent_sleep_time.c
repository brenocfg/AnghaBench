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
struct wakeup_source {int dummy; } ;
typedef  int /*<<< orphan*/  ktime_t ;

/* Variables and functions */

__attribute__((used)) static inline void update_prevent_sleep_time(struct wakeup_source *ws,
					     ktime_t now) {}
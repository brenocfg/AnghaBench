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
struct wacom_wac {TYPE_1__* shared; } ;
struct TYPE_2__ {int /*<<< orphan*/  stylus_in_proximity; } ;

/* Variables and functions */
 scalar_t__ touch_arbitration ; 

__attribute__((used)) static inline bool report_touch_events(struct wacom_wac *wacom)
{
	return (touch_arbitration ? !wacom->shared->stylus_in_proximity : 1);
}
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
typedef  scalar_t__ uint16_t ;
struct cs5535_mfgpt_timer {int nr; TYPE_1__* chip; } ;
struct TYPE_2__ {scalar_t__ base; } ;

/* Variables and functions */
 int /*<<< orphan*/  outw (scalar_t__,scalar_t__) ; 

void cs5535_mfgpt_write(struct cs5535_mfgpt_timer *timer, uint16_t reg,
		uint16_t value)
{
	outw(value, timer->chip->base + reg + (timer->nr * 8));
}
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
struct ads7846 {int /*<<< orphan*/  reg; } ;

/* Variables and functions */
 int /*<<< orphan*/  ads7846_stop (struct ads7846*) ; 
 int /*<<< orphan*/  regulator_disable (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void __ads7846_disable(struct ads7846 *ts)
{
	ads7846_stop(ts);
	regulator_disable(ts->reg);

	/*
	 * We know the chip's in low power mode since we always
	 * leave it that way after every request
	 */
}
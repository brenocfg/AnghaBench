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
struct ir_rx51 {int /*<<< orphan*/  pwm; } ;

/* Variables and functions */
 int /*<<< orphan*/  pwm_enable (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void ir_rx51_on(struct ir_rx51 *ir_rx51)
{
	pwm_enable(ir_rx51->pwm);
}
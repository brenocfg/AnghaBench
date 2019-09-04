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
typedef  int u16 ;
struct lm8323_pwm {int id; int /*<<< orphan*/  chip; } ;

/* Variables and functions */
 int /*<<< orphan*/  LM8323_CMD_PWM_WRITE ; 
 int /*<<< orphan*/  lm8323_write (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int,int) ; 

__attribute__((used)) static void lm8323_write_pwm_one(struct lm8323_pwm *pwm, int pos, u16 cmd)
{
	lm8323_write(pwm->chip, 4, LM8323_CMD_PWM_WRITE, (pos << 2) | pwm->id,
		     (cmd & 0xff00) >> 8, cmd & 0x00ff);
}
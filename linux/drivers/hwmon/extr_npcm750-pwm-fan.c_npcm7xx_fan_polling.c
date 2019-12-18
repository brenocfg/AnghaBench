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
struct timer_list {int dummy; } ;
struct TYPE_2__ {scalar_t__ expires; } ;
struct npcm7xx_pwm_fan_data {int fan_select; TYPE_1__ fan_timer; int /*<<< orphan*/  fan_base; scalar_t__* fan_present; } ;

/* Variables and functions */
 int /*<<< orphan*/  NPCM7XX_FAN_CMPA ; 
 int /*<<< orphan*/  NPCM7XX_FAN_CMPB ; 
 int NPCM7XX_FAN_MAX_MODULE ; 
 int /*<<< orphan*/  NPCM7XX_FAN_POLL_TIMER_200MS ; 
 int /*<<< orphan*/  NPCM7XX_FAN_REG_TCNT1 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  NPCM7XX_FAN_REG_TCNT2 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  NPCM7XX_FAN_REG_TICLR (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  NPCM7XX_FAN_TCNT ; 
 int /*<<< orphan*/  NPCM7XX_FAN_TICLR_CLEAR_ALL ; 
 int /*<<< orphan*/  add_timer (TYPE_1__*) ; 
 int /*<<< orphan*/  fan_timer ; 
 struct npcm7xx_pwm_fan_data* from_timer (struct npcm7xx_pwm_fan_data*,struct timer_list*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iowrite16 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iowrite8 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ jiffies ; 
 scalar_t__ msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  npcm7xx_fan_start_capture (struct npcm7xx_pwm_fan_data*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void npcm7xx_fan_polling(struct timer_list *t)
{
	struct npcm7xx_pwm_fan_data *data;
	int i;

	data = from_timer(data, t, fan_timer);

	/*
	 * Polling two module per one round,
	 * FAN01 & FAN89 / FAN23 & FAN1011 / FAN45 & FAN1213 / FAN67 & FAN1415
	 */
	for (i = data->fan_select; i < NPCM7XX_FAN_MAX_MODULE;
	      i = i + 4) {
		/* clear the flag and reset the counter (TCNT) */
		iowrite8(NPCM7XX_FAN_TICLR_CLEAR_ALL,
			 NPCM7XX_FAN_REG_TICLR(data->fan_base, i));

		if (data->fan_present[i * 2]) {
			iowrite16(NPCM7XX_FAN_TCNT,
				  NPCM7XX_FAN_REG_TCNT1(data->fan_base, i));
			npcm7xx_fan_start_capture(data, i, NPCM7XX_FAN_CMPA);
		}
		if (data->fan_present[(i * 2) + 1]) {
			iowrite16(NPCM7XX_FAN_TCNT,
				  NPCM7XX_FAN_REG_TCNT2(data->fan_base, i));
			npcm7xx_fan_start_capture(data, i, NPCM7XX_FAN_CMPB);
		}
	}

	data->fan_select++;
	data->fan_select &= 0x3;

	/* reset the timer interval */
	data->fan_timer.expires = jiffies +
		msecs_to_jiffies(NPCM7XX_FAN_POLL_TIMER_200MS);
	add_timer(&data->fan_timer);
}
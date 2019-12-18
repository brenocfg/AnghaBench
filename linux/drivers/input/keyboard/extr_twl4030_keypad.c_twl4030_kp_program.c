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
typedef  int u8 ;
struct twl4030_keypad {int /*<<< orphan*/  kp_state; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  KEYP_CTRL ; 
 int KEYP_CTRL_KBD_ON ; 
 int KEYP_CTRL_SOFTMODEN ; 
 int KEYP_CTRL_SOFT_NRST ; 
 int KEYP_CTRL_TOE_EN ; 
 int /*<<< orphan*/  KEYP_DEB ; 
 int /*<<< orphan*/  KEYP_EDR ; 
 int KEYP_EDR_KP_BOTH ; 
 int KEYP_EDR_TO_RISING ; 
 int /*<<< orphan*/  KEYP_LK_PTV ; 
 int KEYP_LK_PTV_PTV_SHIFT ; 
 int KEYP_PERIOD_US (int,int) ; 
 int /*<<< orphan*/  KEYP_SIH_CTRL ; 
 int /*<<< orphan*/  KEYP_TIMEOUT_H ; 
 int /*<<< orphan*/  KEYP_TIMEOUT_L ; 
 int PTV_PRESCALER ; 
 int TWL4030_SIH_CTRL_COR_MASK ; 
 int TWL4030_SIH_CTRL_PENDDIS_MASK ; 
 scalar_t__ twl4030_kpwrite_u8 (struct twl4030_keypad*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ twl4030_read_kp_matrix_state (struct twl4030_keypad*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int twl4030_kp_program(struct twl4030_keypad *kp)
{
	u8 reg;
	int i;

	/* Enable controller, with hardware decoding but not autorepeat */
	reg = KEYP_CTRL_SOFT_NRST | KEYP_CTRL_SOFTMODEN
		| KEYP_CTRL_TOE_EN | KEYP_CTRL_KBD_ON;
	if (twl4030_kpwrite_u8(kp, reg, KEYP_CTRL) < 0)
		return -EIO;

	/*
	 * NOTE: we could use sih_setup() here to package keypad
	 * event sources as four different IRQs ... but we don't.
	 */

	/* Enable TO rising and KP rising and falling edge detection */
	reg = KEYP_EDR_KP_BOTH | KEYP_EDR_TO_RISING;
	if (twl4030_kpwrite_u8(kp, reg, KEYP_EDR) < 0)
		return -EIO;

	/* Set PTV prescaler Field */
	reg = (PTV_PRESCALER << KEYP_LK_PTV_PTV_SHIFT);
	if (twl4030_kpwrite_u8(kp, reg, KEYP_LK_PTV) < 0)
		return -EIO;

	/* Set key debounce time to 20 ms */
	i = KEYP_PERIOD_US(20000, PTV_PRESCALER);
	if (twl4030_kpwrite_u8(kp, i, KEYP_DEB) < 0)
		return -EIO;

	/* Set timeout period to 200 ms */
	i = KEYP_PERIOD_US(200000, PTV_PRESCALER);
	if (twl4030_kpwrite_u8(kp, (i & 0xFF), KEYP_TIMEOUT_L) < 0)
		return -EIO;

	if (twl4030_kpwrite_u8(kp, (i >> 8), KEYP_TIMEOUT_H) < 0)
		return -EIO;

	/*
	 * Enable Clear-on-Read; disable remembering events that fire
	 * after the IRQ but before our handler acks (reads) them.
	 */
	reg = TWL4030_SIH_CTRL_COR_MASK | TWL4030_SIH_CTRL_PENDDIS_MASK;
	if (twl4030_kpwrite_u8(kp, reg, KEYP_SIH_CTRL) < 0)
		return -EIO;

	/* initialize key state; irqs update it from here on */
	if (twl4030_read_kp_matrix_state(kp, kp->kp_state) < 0)
		return -EIO;

	return 0;
}
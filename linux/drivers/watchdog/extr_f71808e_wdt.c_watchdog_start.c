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
typedef  int u8 ;
struct TYPE_2__ {int type; int pulse_val; int /*<<< orphan*/  lock; int /*<<< orphan*/  sioaddr; scalar_t__ pulse_mode; } ;

/* Variables and functions */
 int BIT (int) ; 
 int ENODEV ; 
 int F71808FG_FLAG_WDOUT_EN ; 
 int F71808FG_FLAG_WD_EN ; 
 int F71808FG_FLAG_WD_PULSE ; 
 int /*<<< orphan*/  F71808FG_REG_WDO_CONF ; 
 int /*<<< orphan*/  F71808FG_REG_WDT_CONF ; 
 int F81865_FLAG_WDOUT_EN ; 
 int /*<<< orphan*/  F81865_REG_WDO_CONF ; 
 int /*<<< orphan*/  SIO_F71808FG_LD_WDT ; 
 int /*<<< orphan*/  SIO_F81866_REG_GPIO1 ; 
 int /*<<< orphan*/  SIO_F81866_REG_PORT_SEL ; 
 int /*<<< orphan*/  SIO_REG_CLOCK_SEL ; 
 int /*<<< orphan*/  SIO_REG_ENABLE ; 
 int /*<<< orphan*/  SIO_REG_MFUNCT1 ; 
 int /*<<< orphan*/  SIO_REG_MFUNCT2 ; 
 int /*<<< orphan*/  SIO_REG_MFUNCT3 ; 
 int /*<<< orphan*/  SIO_REG_TSI_LEVEL_SEL ; 
#define  f71808fg 136 
#define  f71862fg 135 
 int f71862fg_pin_configure (int /*<<< orphan*/ ) ; 
#define  f71868 134 
#define  f71869 133 
#define  f71882fg 132 
#define  f71889fg 131 
#define  f81803 130 
#define  f81865 129 
#define  f81866 128 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  superio_clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int superio_enter (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  superio_exit (int /*<<< orphan*/ ) ; 
 int superio_inb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  superio_outb (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  superio_select (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  superio_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 TYPE_1__ watchdog ; 
 int watchdog_keepalive () ; 

__attribute__((used)) static int watchdog_start(void)
{
	int err;
	u8 tmp;

	/* Make sure we don't die as soon as the watchdog is enabled below */
	err = watchdog_keepalive();
	if (err)
		return err;

	mutex_lock(&watchdog.lock);
	err = superio_enter(watchdog.sioaddr);
	if (err)
		goto exit_unlock;
	superio_select(watchdog.sioaddr, SIO_F71808FG_LD_WDT);

	/* Watchdog pin configuration */
	switch (watchdog.type) {
	case f71808fg:
		/* Set pin 21 to GPIO23/WDTRST#, then to WDTRST# */
		superio_clear_bit(watchdog.sioaddr, SIO_REG_MFUNCT2, 3);
		superio_clear_bit(watchdog.sioaddr, SIO_REG_MFUNCT3, 3);
		break;

	case f71862fg:
		err = f71862fg_pin_configure(watchdog.sioaddr);
		if (err)
			goto exit_superio;
		break;

	case f71868:
	case f71869:
		/* GPIO14 --> WDTRST# */
		superio_clear_bit(watchdog.sioaddr, SIO_REG_MFUNCT1, 4);
		break;

	case f71882fg:
		/* Set pin 56 to WDTRST# */
		superio_set_bit(watchdog.sioaddr, SIO_REG_MFUNCT1, 1);
		break;

	case f71889fg:
		/* set pin 40 to WDTRST# */
		superio_outb(watchdog.sioaddr, SIO_REG_MFUNCT3,
			superio_inb(watchdog.sioaddr, SIO_REG_MFUNCT3) & 0xcf);
		break;

	case f81803:
		/* Enable TSI Level register bank */
		superio_clear_bit(watchdog.sioaddr, SIO_REG_CLOCK_SEL, 3);
		/* Set pin 27 to WDTRST# */
		superio_outb(watchdog.sioaddr, SIO_REG_TSI_LEVEL_SEL, 0x5f &
			superio_inb(watchdog.sioaddr, SIO_REG_TSI_LEVEL_SEL));
		break;

	case f81865:
		/* Set pin 70 to WDTRST# */
		superio_clear_bit(watchdog.sioaddr, SIO_REG_MFUNCT3, 5);
		break;

	case f81866:
		/*
		 * GPIO1 Control Register when 27h BIT3:2 = 01 & BIT0 = 0.
		 * The PIN 70(GPIO15/WDTRST) is controlled by 2Ch:
		 *     BIT5: 0 -> WDTRST#
		 *           1 -> GPIO15
		 */
		tmp = superio_inb(watchdog.sioaddr, SIO_F81866_REG_PORT_SEL);
		tmp &= ~(BIT(3) | BIT(0));
		tmp |= BIT(2);
		superio_outb(watchdog.sioaddr, SIO_F81866_REG_PORT_SEL, tmp);

		superio_clear_bit(watchdog.sioaddr, SIO_F81866_REG_GPIO1, 5);
		break;

	default:
		/*
		 * 'default' label to shut up the compiler and catch
		 * programmer errors
		 */
		err = -ENODEV;
		goto exit_superio;
	}

	superio_select(watchdog.sioaddr, SIO_F71808FG_LD_WDT);
	superio_set_bit(watchdog.sioaddr, SIO_REG_ENABLE, 0);

	if (watchdog.type == f81865 || watchdog.type == f81866)
		superio_set_bit(watchdog.sioaddr, F81865_REG_WDO_CONF,
				F81865_FLAG_WDOUT_EN);
	else
		superio_set_bit(watchdog.sioaddr, F71808FG_REG_WDO_CONF,
				F71808FG_FLAG_WDOUT_EN);

	superio_set_bit(watchdog.sioaddr, F71808FG_REG_WDT_CONF,
			F71808FG_FLAG_WD_EN);

	if (watchdog.pulse_mode) {
		/* Select "pulse" output mode with given duration */
		u8 wdt_conf = superio_inb(watchdog.sioaddr,
				F71808FG_REG_WDT_CONF);

		/* Set WD_PSWIDTH bits (1:0) */
		wdt_conf = (wdt_conf & 0xfc) | (watchdog.pulse_val & 0x03);
		/* Set WD_PULSE to "pulse" mode */
		wdt_conf |= BIT(F71808FG_FLAG_WD_PULSE);

		superio_outb(watchdog.sioaddr, F71808FG_REG_WDT_CONF,
				wdt_conf);
	} else {
		/* Select "level" output mode */
		superio_clear_bit(watchdog.sioaddr, F71808FG_REG_WDT_CONF,
				F71808FG_FLAG_WD_PULSE);
	}

exit_superio:
	superio_exit(watchdog.sioaddr);
exit_unlock:
	mutex_unlock(&watchdog.lock);

	return err;
}
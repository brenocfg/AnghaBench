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
typedef  int /*<<< orphan*/  u8 ;
struct mutex {int dummy; } ;
struct ds1685_priv {int (* read ) (struct ds1685_priv*,scalar_t__) ;int /*<<< orphan*/  (* write ) (struct ds1685_priv*,scalar_t__,int) ;TYPE_1__* dev; } ;
typedef  scalar_t__ ssize_t ;
struct TYPE_2__ {struct mutex ops_lock; } ;

/* Variables and functions */
 scalar_t__ NVRAM_BANK0_BASE ; 
 scalar_t__ NVRAM_SZ_TIME ; 
 scalar_t__ NVRAM_TIME_BASE ; 
 unsigned int NVRAM_TOTAL_SZ ; 
 unsigned int NVRAM_TOTAL_SZ_BANK0 ; 
 scalar_t__ RTC_BANK1_RAM_ADDR ; 
 scalar_t__ RTC_BANK1_RAM_ADDR_LSB ; 
 scalar_t__ RTC_BANK1_RAM_DATA_PORT ; 
 int RTC_CTRL_4A_BME ; 
 scalar_t__ RTC_EXT_CTRL_4A ; 
 int /*<<< orphan*/  ds1685_rtc_switch_to_bank0 (struct ds1685_priv*) ; 
 int /*<<< orphan*/  ds1685_rtc_switch_to_bank1 (struct ds1685_priv*) ; 
 int mutex_lock_interruptible (struct mutex*) ; 
 int /*<<< orphan*/  mutex_unlock (struct mutex*) ; 
 int stub1 (struct ds1685_priv*,scalar_t__) ; 
 int stub2 (struct ds1685_priv*,scalar_t__) ; 
 int /*<<< orphan*/  stub3 (struct ds1685_priv*,scalar_t__,int) ; 
 int stub4 (struct ds1685_priv*,scalar_t__) ; 
 int /*<<< orphan*/  stub5 (struct ds1685_priv*,scalar_t__,unsigned int) ; 
 int /*<<< orphan*/  stub6 (struct ds1685_priv*,scalar_t__,unsigned int) ; 
 int stub7 (struct ds1685_priv*,scalar_t__) ; 
 int /*<<< orphan*/  stub8 (struct ds1685_priv*,scalar_t__,int) ; 
 int stub9 (struct ds1685_priv*,scalar_t__) ; 

__attribute__((used)) static int ds1685_nvram_read(void *priv, unsigned int pos, void *val,
			     size_t size)
{
	struct ds1685_priv *rtc = priv;
	struct mutex *rtc_mutex = &rtc->dev->ops_lock;
	ssize_t count;
	u8 *buf = val;
	int err;

	err = mutex_lock_interruptible(rtc_mutex);
	if (err)
		return err;

	ds1685_rtc_switch_to_bank0(rtc);

	/* Read NVRAM in time and bank0 registers. */
	for (count = 0; size > 0 && pos < NVRAM_TOTAL_SZ_BANK0;
	     count++, size--) {
		if (count < NVRAM_SZ_TIME)
			*buf++ = rtc->read(rtc, (NVRAM_TIME_BASE + pos++));
		else
			*buf++ = rtc->read(rtc, (NVRAM_BANK0_BASE + pos++));
	}

#ifndef CONFIG_RTC_DRV_DS1689
	if (size > 0) {
		ds1685_rtc_switch_to_bank1(rtc);

#ifndef CONFIG_RTC_DRV_DS1685
		/* Enable burst-mode on DS17x85/DS17x87 */
		rtc->write(rtc, RTC_EXT_CTRL_4A,
			   (rtc->read(rtc, RTC_EXT_CTRL_4A) |
			    RTC_CTRL_4A_BME));

		/* We need one write to RTC_BANK1_RAM_ADDR_LSB to start
		 * reading with burst-mode */
		rtc->write(rtc, RTC_BANK1_RAM_ADDR_LSB,
			   (pos - NVRAM_TOTAL_SZ_BANK0));
#endif

		/* Read NVRAM in bank1 registers. */
		for (count = 0; size > 0 && pos < NVRAM_TOTAL_SZ;
		     count++, size--) {
#ifdef CONFIG_RTC_DRV_DS1685
			/* DS1685/DS1687 has to write to RTC_BANK1_RAM_ADDR
			 * before each read. */
			rtc->write(rtc, RTC_BANK1_RAM_ADDR,
				   (pos - NVRAM_TOTAL_SZ_BANK0));
#endif
			*buf++ = rtc->read(rtc, RTC_BANK1_RAM_DATA_PORT);
			pos++;
		}

#ifndef CONFIG_RTC_DRV_DS1685
		/* Disable burst-mode on DS17x85/DS17x87 */
		rtc->write(rtc, RTC_EXT_CTRL_4A,
			   (rtc->read(rtc, RTC_EXT_CTRL_4A) &
			    ~(RTC_CTRL_4A_BME)));
#endif
		ds1685_rtc_switch_to_bank0(rtc);
	}
#endif /* !CONFIG_RTC_DRV_DS1689 */
	mutex_unlock(rtc_mutex);

	return 0;
}
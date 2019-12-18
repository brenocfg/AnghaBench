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
struct cr0014114 {int do_recount; size_t count; scalar_t__ delay; int /*<<< orphan*/ * buf; int /*<<< orphan*/  spi; TYPE_1__* leds; } ;
struct TYPE_2__ {int /*<<< orphan*/  brightness; } ;

/* Variables and functions */
 int /*<<< orphan*/  CR_FW_DELAY_MSEC ; 
 int /*<<< orphan*/  CR_SET_BRIGHTNESS ; 
 int /*<<< orphan*/  cr0014114_calc_crc (int /*<<< orphan*/ *,int) ; 
 int cr0014114_recount (struct cr0014114*) ; 
 unsigned long jiffies ; 
 unsigned long jiffies_to_usecs (scalar_t__) ; 
 scalar_t__ msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msleep (int /*<<< orphan*/ ) ; 
 int spi_write (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 scalar_t__ time_after (scalar_t__,unsigned long) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  usleep_range (unsigned long,unsigned long) ; 

__attribute__((used)) static int cr0014114_sync(struct cr0014114 *priv)
{
	int		ret;
	size_t		i;
	unsigned long	udelay, now = jiffies;

	/* to avoid SPI mistiming with firmware we should wait some time */
	if (time_after(priv->delay, now)) {
		udelay = jiffies_to_usecs(priv->delay - now);
		usleep_range(udelay, udelay + 1);
	}

	if (unlikely(priv->do_recount)) {
		ret = cr0014114_recount(priv);
		if (ret)
			goto err;

		priv->do_recount = false;
		msleep(CR_FW_DELAY_MSEC);
	}

	priv->buf[0] = CR_SET_BRIGHTNESS;
	for (i = 0; i < priv->count; i++)
		priv->buf[i + 1] = priv->leds[i].brightness;
	cr0014114_calc_crc(priv->buf, priv->count + 2);
	ret = spi_write(priv->spi, priv->buf, priv->count + 2);

err:
	priv->delay = jiffies + msecs_to_jiffies(CR_FW_DELAY_MSEC);

	return ret;
}
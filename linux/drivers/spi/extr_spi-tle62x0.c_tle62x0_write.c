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
struct tle62x0_state {unsigned char* tx_buff; unsigned int gpio_state; int nr_gpio; TYPE_1__* us; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 unsigned char CMD_SET ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,unsigned char*) ; 
 int spi_write (TYPE_1__*,unsigned char*,int) ; 

__attribute__((used)) static inline int tle62x0_write(struct tle62x0_state *st)
{
	unsigned char *buff = st->tx_buff;
	unsigned int gpio_state = st->gpio_state;

	buff[0] = CMD_SET;

	if (st->nr_gpio == 16) {
		buff[1] = gpio_state >> 8;
		buff[2] = gpio_state;
	} else {
		buff[1] = gpio_state;
	}

	dev_dbg(&st->us->dev, "buff %3ph\n", buff);

	return spi_write(st->us, buff, (st->nr_gpio == 16) ? 3 : 2);
}
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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u16 ;
struct ts_nbus {int /*<<< orphan*/  lock; int /*<<< orphan*/  csn; int /*<<< orphan*/  rdy; int /*<<< orphan*/  txrx; } ;

/* Variables and functions */
 int /*<<< orphan*/  TS_NBUS_WRITE_ADR ; 
 int /*<<< orphan*/  TS_NBUS_WRITE_VAL ; 
 scalar_t__ gpiod_get_value_cansleep (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpiod_set_value_cansleep (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ts_nbus_write_bus (struct ts_nbus*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int ts_nbus_write(struct ts_nbus *ts_nbus, u8 adr, u16 val)
{
	int i;

	/* bus access must be atomic */
	mutex_lock(&ts_nbus->lock);

	/* set the bus in write mode */
	gpiod_set_value_cansleep(ts_nbus->txrx, 1);

	/* write address */
	ts_nbus_write_bus(ts_nbus, TS_NBUS_WRITE_ADR, adr);

	/* writing value MSB first */
	for (i = 1; i >= 0; i--)
		ts_nbus_write_bus(ts_nbus, TS_NBUS_WRITE_VAL, (u8)(val >> (i * 8)));

	/* wait for completion */
	gpiod_set_value_cansleep(ts_nbus->csn, 1);
	while (gpiod_get_value_cansleep(ts_nbus->rdy) != 0) {
		gpiod_set_value_cansleep(ts_nbus->csn, 0);
		gpiod_set_value_cansleep(ts_nbus->csn, 1);
	}

	mutex_unlock(&ts_nbus->lock);

	return 0;
}
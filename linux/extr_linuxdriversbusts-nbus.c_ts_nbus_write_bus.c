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
struct ts_nbus {int /*<<< orphan*/  ale; } ;

/* Variables and functions */
 int TS_NBUS_WRITE_ADR ; 
 int /*<<< orphan*/  gpiod_set_value_cansleep (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ts_nbus_reset_bus (struct ts_nbus*) ; 
 int /*<<< orphan*/  ts_nbus_start_transaction (struct ts_nbus*) ; 
 int /*<<< orphan*/  ts_nbus_write_byte (struct ts_nbus*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ts_nbus_write_bus(struct ts_nbus *ts_nbus, int cmd, u8 val)
{
	ts_nbus_reset_bus(ts_nbus);

	if (cmd == TS_NBUS_WRITE_ADR)
		gpiod_set_value_cansleep(ts_nbus->ale, 1);

	ts_nbus_write_byte(ts_nbus, val);
	ts_nbus_start_transaction(ts_nbus);
}
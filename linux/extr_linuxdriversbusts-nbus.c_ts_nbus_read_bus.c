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
struct ts_nbus {int dummy; } ;

/* Variables and functions */
 int ts_nbus_read_byte (struct ts_nbus*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ts_nbus_reset_bus (struct ts_nbus*) ; 
 int /*<<< orphan*/  ts_nbus_start_transaction (struct ts_nbus*) ; 

__attribute__((used)) static int ts_nbus_read_bus(struct ts_nbus *ts_nbus, u8 *val)
{
	ts_nbus_reset_bus(ts_nbus);
	ts_nbus_start_transaction(ts_nbus);

	return ts_nbus_read_byte(ts_nbus, val);
}
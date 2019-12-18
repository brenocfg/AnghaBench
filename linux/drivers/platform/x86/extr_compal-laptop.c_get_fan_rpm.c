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
typedef  scalar_t__ u8 ;

/* Variables and functions */
 int /*<<< orphan*/  FAN_ADDRESS ; 
 scalar_t__ FAN_DATA ; 
 int /*<<< orphan*/  ec_transaction (int /*<<< orphan*/ ,scalar_t__*,int,scalar_t__*,int) ; 

__attribute__((used)) static int get_fan_rpm(void)
{
	u8 value, data = FAN_DATA;
	ec_transaction(FAN_ADDRESS, &data, 1, &value, 1);
	return 100 * (int)value;
}
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
struct TYPE_2__ {int fan_level; scalar_t__ casetemp; scalar_t__ temp; int /*<<< orphan*/  fan; } ;

/* Variables and functions */
 int /*<<< orphan*/  print_temp (char*,scalar_t__) ; 
 int /*<<< orphan*/  printk (char*,int,int) ; 
 int /*<<< orphan*/  write_reg (int /*<<< orphan*/ ,int,int,int) ; 
 TYPE_1__ x ; 

__attribute__((used)) static void
tune_fan( int fan_setting )
{
	int val = (fan_setting << 3) | 7;

	/* write_reg( x.fan, 0x24, val, 1 ); */
	write_reg( x.fan, 0x25, val, 1 );
	write_reg( x.fan, 0x20, 0, 1 );
	print_temp("CPU-temp: ", x.temp );
	if( x.casetemp )
		print_temp(", Case: ", x.casetemp );
	printk(",  Fan: %d (tuned %+d)\n", 11-fan_setting, x.fan_level-fan_setting );

	x.fan_level = fan_setting;
}
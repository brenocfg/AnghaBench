#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int temp; int fan_down_setting; int fan_up_setting; } ;
struct TYPE_3__ {int temp; int casetemp; int downind; int upind; scalar_t__ fan_level; int /*<<< orphan*/  fan; int /*<<< orphan*/  thermostat; } ;

/* Variables and functions */
 scalar_t__ LOG_TEMP ; 
 TYPE_2__* fan_table ; 
 int /*<<< orphan*/  print_temp (char*,int) ; 
 int /*<<< orphan*/  printk (char*,scalar_t__) ; 
 int read_reg (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  tune_fan (int) ; 
 TYPE_1__ x ; 

__attribute__((used)) static void
poll_temp( void )
{
	int temp, i, level, casetemp;

	temp = read_reg( x.thermostat, 0, 2 );

	/* this actually occurs when the computer is loaded */
	if( temp < 0 )
		return;

	casetemp = read_reg(x.fan, 0x0b, 1) << 8;
	casetemp |= (read_reg(x.fan, 0x06, 1) & 0x7) << 5;

	if( LOG_TEMP && x.temp != temp ) {
		print_temp("CPU-temp: ", temp );
		print_temp(", Case: ", casetemp );
		printk(",  Fan: %d\n", 11-x.fan_level );
	}
	x.temp = temp;
	x.casetemp = casetemp;

	level = -1;
	for( i=0; (temp & 0xffff) > fan_table[i].temp ; i++ )
		;
	if( i < x.downind )
		level = fan_table[i].fan_down_setting;
	x.downind = i;

	for( i=0; (temp & 0xffff) >= fan_table[i+1].temp ; i++ )
		;
	if( x.upind < i )
		level = fan_table[i].fan_up_setting;
	x.upind = i;

	if( level >= 0 )
		tune_fan( level );
}
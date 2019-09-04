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
struct therm {int /*<<< orphan*/  hi; int /*<<< orphan*/  lo; } ;

/* Variables and functions */
 int /*<<< orphan*/  CFG_CPU ; 
 int /*<<< orphan*/  THERM_START_CONVERT ; 
 int /*<<< orphan*/  THERM_WRITE_CONFIG ; 
 int /*<<< orphan*/  THERM_WRITE_TH ; 
 int /*<<< orphan*/  THERM_WRITE_TL ; 
 int /*<<< orphan*/  ds1620_out (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ds1620_write_state(struct therm *therm)
{
	ds1620_out(THERM_WRITE_CONFIG, 8, CFG_CPU);
	ds1620_out(THERM_WRITE_TL, 9, therm->lo);
	ds1620_out(THERM_WRITE_TH, 9, therm->hi);
	ds1620_out(THERM_START_CONVERT, 0, 0);
}
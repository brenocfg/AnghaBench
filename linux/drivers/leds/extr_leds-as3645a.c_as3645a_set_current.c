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
typedef  int u8 ;
struct as3645a {int flash_current; int assist_current; } ;

/* Variables and functions */
 int AS_CURRENT_ASSIST_LIGHT_SHIFT ; 
 int AS_CURRENT_FLASH_CURRENT_SHIFT ; 
 int AS_CURRENT_LED_DET_ON ; 
 int /*<<< orphan*/  AS_CURRENT_SET_REG ; 
 int as3645a_write (struct as3645a*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int as3645a_set_current(struct as3645a *flash)
{
	u8 val;

	val = (flash->flash_current << AS_CURRENT_FLASH_CURRENT_SHIFT)
	    | (flash->assist_current << AS_CURRENT_ASSIST_LIGHT_SHIFT)
	    | AS_CURRENT_LED_DET_ON;

	return as3645a_write(flash, AS_CURRENT_SET_REG, val);
}
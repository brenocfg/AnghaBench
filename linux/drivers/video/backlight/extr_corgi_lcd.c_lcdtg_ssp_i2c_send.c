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
typedef  int /*<<< orphan*/  uint8_t ;
struct corgi_lcd {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  POWERREG0_ADRS ; 
 int /*<<< orphan*/  corgi_ssp_lcdtg_send (struct corgi_lcd*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void lcdtg_ssp_i2c_send(struct corgi_lcd *lcd, uint8_t data)
{
	corgi_ssp_lcdtg_send(lcd, POWERREG0_ADRS, data);
	udelay(10);
}
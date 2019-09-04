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
struct bd2802_led_platform_data {int /*<<< orphan*/  rgb_time; } ;
struct bd2802_led {int /*<<< orphan*/  client; struct bd2802_led_platform_data* pdata; } ;

/* Variables and functions */
 int /*<<< orphan*/  BD2802_REG_HOURSETUP ; 
 int /*<<< orphan*/  LED1 ; 
 int /*<<< orphan*/  LED2 ; 
 int /*<<< orphan*/  RED ; 
 int /*<<< orphan*/  bd2802_get_reg_addr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bd2802_write_byte (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void bd2802_configure(struct bd2802_led *led)
{
	struct bd2802_led_platform_data *pdata = led->pdata;
	u8 reg;

	reg = bd2802_get_reg_addr(LED1, RED, BD2802_REG_HOURSETUP);
	bd2802_write_byte(led->client, reg, pdata->rgb_time);

	reg = bd2802_get_reg_addr(LED2, RED, BD2802_REG_HOURSETUP);
	bd2802_write_byte(led->client, reg, pdata->rgb_time);
}
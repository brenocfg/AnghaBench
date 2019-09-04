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
typedef  int u16 ;
struct broadsheetfb_par {int dummy; } ;

/* Variables and functions */
 int DB0_GPIO_PIN ; 
 int DB15_GPIO_PIN ; 
 int /*<<< orphan*/  gpio_set_value (int,int) ; 

__attribute__((used)) static void am300_set_hdb(struct broadsheetfb_par *par, u16 data)
{
	int i;

	for (i = 0; i <= (DB15_GPIO_PIN - DB0_GPIO_PIN) ; i++)
		gpio_set_value(DB0_GPIO_PIN + i, (data >> i) & 0x01);
}
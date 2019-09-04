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
struct hd44780 {int dummy; } ;
struct charlcd {struct hd44780* drvdata; } ;

/* Variables and functions */
 int /*<<< orphan*/  hd44780_write_gpio8 (struct hd44780*,int,int) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void hd44780_write_data_gpio8(struct charlcd *lcd, int data)
{
	struct hd44780 *hd = lcd->drvdata;

	hd44780_write_gpio8(hd, data, 1);

	/* The shortest data takes at least 45 us */
	udelay(45);
}
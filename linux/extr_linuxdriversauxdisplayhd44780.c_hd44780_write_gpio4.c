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
struct hd44780 {scalar_t__* pins; } ;

/* Variables and functions */
 int BIT (unsigned int) ; 
 size_t PIN_CTRL_RS ; 
 size_t PIN_CTRL_RW ; 
 unsigned int PIN_DATA0 ; 
 size_t PIN_DATA4 ; 
 int /*<<< orphan*/  gpiod_set_array_value_cansleep (unsigned int,scalar_t__*,int*) ; 
 int /*<<< orphan*/  hd44780_strobe_gpio (struct hd44780*) ; 

__attribute__((used)) static void hd44780_write_gpio4(struct hd44780 *hd, u8 val, unsigned int rs)
{
	int values[10];	/* for DATA[0-7], RS, RW, but DATA[0-3] is unused */
	unsigned int i, n;

	/* High nibble + RS, RW */
	for (i = 4; i < 8; i++)
		values[PIN_DATA0 + i] = !!(val & BIT(i));
	values[PIN_CTRL_RS] = rs;
	n = 5;
	if (hd->pins[PIN_CTRL_RW]) {
		values[PIN_CTRL_RW] = 0;
		n++;
	}

	/* Present the data to the port */
	gpiod_set_array_value_cansleep(n, &hd->pins[PIN_DATA4],
				       &values[PIN_DATA4]);

	hd44780_strobe_gpio(hd);

	/* Low nibble */
	for (i = 0; i < 4; i++)
		values[PIN_DATA4 + i] = !!(val & BIT(i));

	/* Present the data to the port */
	gpiod_set_array_value_cansleep(n, &hd->pins[PIN_DATA4],
				       &values[PIN_DATA4]);

	hd44780_strobe_gpio(hd);
}
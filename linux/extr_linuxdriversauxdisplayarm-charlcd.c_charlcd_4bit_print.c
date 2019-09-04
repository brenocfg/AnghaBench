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
struct charlcd {int dummy; } ;

/* Variables and functions */
 int HD_SET_DDRAM ; 
 int /*<<< orphan*/  charlcd_4bit_char (struct charlcd*,char const) ; 
 int /*<<< orphan*/  charlcd_4bit_command (struct charlcd*,int) ; 
 int strlen (char const*) ; 

__attribute__((used)) static void charlcd_4bit_print(struct charlcd *lcd, int line, const char *str)
{
	u8 offset;
	int i;

	/*
	 * We support line 0, 1
	 * Line 1 runs from 0x00..0x27
	 * Line 2 runs from 0x28..0x4f
	 */
	if (line == 0)
		offset = 0;
	else if (line == 1)
		offset = 0x28;
	else
		return;

	/* Set offset */
	charlcd_4bit_command(lcd, HD_SET_DDRAM | offset);

	/* Send string */
	for (i = 0; i < strlen(str) && i < 0x28; i++)
		charlcd_4bit_char(lcd, str[i]);
}
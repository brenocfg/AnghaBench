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

/* Variables and functions */

__attribute__((used)) static bool char_allowed(int c)
{
	/*
	 * Permitted Characters : Alphanumeric, hyphen, underscore, comma
	 */
	if ((c >= 0x30 && c <= 0x39) /* digits */ ||
		(c >= 0x41 && c <= 0x5A) /* upper case */ ||
		(c >= 0x61 && c <= 0x7A) /* lower case */ ||
		c == 0 /* NULL */ ||
		c == 0x2D /* - */ ||
		c == 0x5F /* _ */ ||
		c == 0x2C /* , */)
		return true;
	return false;
}
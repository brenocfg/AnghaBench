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
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 

__attribute__((used)) static char *__strip_trailing_space(char *buf, char *str, int len)
{
	int i = len - 1;

	memcpy(buf, str, len);
	buf[len] = '\0';
	while (i >= 0 && buf[i] == ' ')
		buf[i--] = '\0';
	return buf;
}
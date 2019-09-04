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
 char const* __strend (char const*) ; 
 int /*<<< orphan*/  memcpy (char*,char const*,size_t) ; 

size_t strlcpy(char *dest, const char *src, size_t size)
{
	size_t ret = __strend(src) - src;

	if (size) {
		size_t len = (ret >= size) ? size-1 : ret;
		dest[len] = '\0';
		memcpy(dest, src, len);
	}
	return ret;
}
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

size_t strlcat(char *dest, const char *src, size_t n)
{
	size_t dsize = __strend(dest) - dest;
	size_t len = __strend(src) - src;
	size_t res = dsize + len;

	if (dsize < n) {
		dest += dsize;
		n -= dsize;
		if (len >= n)
			len = n - 1;
		dest[len] = '\0';
		memcpy(dest, src, len);
	}
	return res;
}
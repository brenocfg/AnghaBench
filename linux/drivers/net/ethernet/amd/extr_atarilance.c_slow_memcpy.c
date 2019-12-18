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
 int /*<<< orphan*/  MFPDELAY () ; 

__attribute__((used)) static void *slow_memcpy( void *dst, const void *src, size_t len )

{	char *cto = dst;
	const char *cfrom = src;

	while( len-- ) {
		*cto++ = *cfrom++;
		MFPDELAY();
	}
	return dst;
}
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
typedef  int u32 ;

/* Variables and functions */

__attribute__((used)) static inline void jcopy(u8 *dest, const u8 *src, u32 n)
{
	switch (n) {
	case 7:
		*dest++ = *src++;
		/* fall through */
	case 6:
		*dest++ = *src++;
		/* fall through */
	case 5:
		*dest++ = *src++;
		/* fall through */
	case 4:
		*dest++ = *src++;
		/* fall through */
	case 3:
		*dest++ = *src++;
		/* fall through */
	case 2:
		*dest++ = *src++;
		/* fall through */
	case 1:
		*dest++ = *src++;
		/* fall through */
	}
}
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
typedef  int u16 ;

/* Variables and functions */

__attribute__((used)) static inline u8 cip2si1(u16 cipval)
{
	static const u8 si[32] =
		{7, 1, 7, 7, 1, 1, 7, 7,	/*0-7 */
		 7, 1, 0, 0, 0, 0, 0, 0,	/*8-15 */
		 1, 2, 4, 10, 9, 9, 15, 7,	/*16-23 */
		 7, 7, 1, 16, 16, 0, 0, 0};	/*24-31 */

	if (cipval > 31)
		cipval = 0;	/* .... */
	return si[cipval];
}
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
typedef  int /*<<< orphan*/  u16 ;
struct vc_data {int dummy; } ;
typedef  int a ;

/* Variables and functions */

__attribute__((used)) static void
sisusbcon_invert_region(struct vc_data *vc, u16 *p, int count)
{
	/* Invert a region. This is called with a pointer
	 * to the console's internal screen buffer. So we
	 * simply do the inversion there and rely on
	 * a call to putc(s) to update the real screen.
	 */

	while (count--) {
		u16 a = *p;

		*p++ = ((a) & 0x88ff)        |
		       (((a) & 0x7000) >> 4) |
		       (((a) & 0x0700) << 4);
	}
}
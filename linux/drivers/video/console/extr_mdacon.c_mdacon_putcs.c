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

/* Variables and functions */
 int /*<<< orphan*/ * mda_addr (int,int) ; 
 int /*<<< orphan*/  mda_convert_attr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scr_readw (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scr_writew (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mdacon_putcs(struct vc_data *c, const unsigned short *s,
		         int count, int y, int x)
{
	u16 *dest = mda_addr(x, y);

	for (; count > 0; count--) {
		scr_writew(mda_convert_attr(scr_readw(s++)), dest++);
	}
}
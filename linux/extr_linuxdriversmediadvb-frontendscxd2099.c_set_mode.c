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
struct cxd {int mode; } ;

/* Variables and functions */
 int /*<<< orphan*/  write_regm (struct cxd*,int,int,int) ; 

__attribute__((used)) static void set_mode(struct cxd *ci, int mode)
{
	if (mode == ci->mode)
		return;

	switch (mode) {
	case 0x00: /* IO mem */
		write_regm(ci, 0x06, 0x00, 0x07);
		break;
	case 0x01: /* ATT mem */
		write_regm(ci, 0x06, 0x02, 0x07);
		break;
	default:
		break;
	}
	ci->mode = mode;
}
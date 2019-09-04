#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_4__ {int /*<<< orphan*/  read_data; } ;
struct cxd {int cammode; TYPE_1__* client; int /*<<< orphan*/  write_busy; TYPE_2__ en; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  read_reg (struct cxd*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_reg (struct cxd*,int,int) ; 
 int /*<<< orphan*/  write_regm (struct cxd*,int,int,int) ; 

__attribute__((used)) static void cam_mode(struct cxd *ci, int mode)
{
	u8 dummy;

	if (mode == ci->cammode)
		return;

	switch (mode) {
	case 0x00:
		write_regm(ci, 0x20, 0x80, 0x80);
		break;
	case 0x01:
		if (!ci->en.read_data)
			return;
		ci->write_busy = 0;
		dev_info(&ci->client->dev, "enable cam buffer mode\n");
		write_reg(ci, 0x0d, 0x00);
		write_reg(ci, 0x0e, 0x01);
		write_regm(ci, 0x08, 0x40, 0x40);
		read_reg(ci, 0x12, &dummy);
		write_regm(ci, 0x08, 0x80, 0x80);
		break;
	default:
		break;
	}
	ci->cammode = mode;
}
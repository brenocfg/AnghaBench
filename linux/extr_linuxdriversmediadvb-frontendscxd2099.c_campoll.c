#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct cxd {int dr; int slot_stat; int ready; TYPE_1__* client; scalar_t__ write_busy; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int DVB_CA_EN50221_POLL_CAM_PRESENT ; 
 int DVB_CA_EN50221_POLL_CAM_READY ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  read_reg (struct cxd*,int,int*) ; 
 int /*<<< orphan*/  write_reg (struct cxd*,int,int) ; 
 int /*<<< orphan*/  write_regm (struct cxd*,int,int,int) ; 

__attribute__((used)) static int campoll(struct cxd *ci)
{
	u8 istat;

	read_reg(ci, 0x04, &istat);
	if (!istat)
		return 0;
	write_reg(ci, 0x05, istat);

	if (istat & 0x40)
		ci->dr = 1;
	if (istat & 0x20)
		ci->write_busy = 0;

	if (istat & 2) {
		u8 slotstat;

		read_reg(ci, 0x01, &slotstat);
		if (!(2 & slotstat)) {
			if (!ci->slot_stat) {
				ci->slot_stat |=
					      DVB_CA_EN50221_POLL_CAM_PRESENT;
				write_regm(ci, 0x03, 0x08, 0x08);
			}

		} else {
			if (ci->slot_stat) {
				ci->slot_stat = 0;
				write_regm(ci, 0x03, 0x00, 0x08);
				dev_info(&ci->client->dev, "NO CAM\n");
				ci->ready = 0;
			}
		}
		if ((istat & 8) &&
		    ci->slot_stat == DVB_CA_EN50221_POLL_CAM_PRESENT) {
			ci->ready = 1;
			ci->slot_stat |= DVB_CA_EN50221_POLL_CAM_READY;
		}
	}
	return 0;
}
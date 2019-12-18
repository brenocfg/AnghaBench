#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct ddb_output {TYPE_2__* port; } ;
struct ddb {TYPE_4__* link; } ;
struct TYPE_7__ {int regmapid; } ;
struct TYPE_8__ {TYPE_3__ ids; TYPE_1__* info; } ;
struct TYPE_6__ {int obr; int gap; int nr; struct ddb* dev; } ;
struct TYPE_5__ {scalar_t__ type; } ;

/* Variables and functions */
 scalar_t__ DDB_OCTOPUS_CI ; 

__attribute__((used)) static void calc_con(struct ddb_output *output, u32 *con, u32 *con2, u32 flags)
{
	struct ddb *dev = output->port->dev;
	u32 bitrate = output->port->obr, max_bitrate = 72000;
	u32 gap = 4, nco = 0;

	*con = 0x1c;
	if (output->port->gap != 0xffffffff) {
		flags |= 1;
		gap = output->port->gap;
		max_bitrate = 0;
	}
	if (dev->link[0].info->type == DDB_OCTOPUS_CI && output->port->nr > 1) {
		*con = 0x10c;
		if (dev->link[0].ids.regmapid >= 0x10003 && !(flags & 1)) {
			if (!(flags & 2)) {
				/* NCO */
				max_bitrate = 0;
				gap = 0;
				if (bitrate != 72000) {
					if (bitrate >= 96000) {
						*con |= 0x800;
					} else {
						*con |= 0x1000;
						nco = (bitrate * 8192 + 71999)
							/ 72000;
					}
				}
			} else {
				/* Divider and gap */
				*con |= 0x1810;
				if (bitrate <= 64000) {
					max_bitrate = 64000;
					nco = 8;
				} else if (bitrate <= 72000) {
					max_bitrate = 72000;
					nco = 7;
				} else {
					max_bitrate = 96000;
					nco = 5;
				}
			}
		} else {
			if (bitrate > 72000) {
				*con |= 0x810; /* 96 MBit/s and gap */
				max_bitrate = 96000;
			}
			*con |= 0x10; /* enable gap */
		}
	}
	if (max_bitrate > 0) {
		if (bitrate > max_bitrate)
			bitrate = max_bitrate;
		if (bitrate < 31000)
			bitrate = 31000;
		gap = ((max_bitrate - bitrate) * 94) / bitrate;
		if (gap < 2)
			*con &= ~0x10; /* Disable gap */
		else
			gap -= 2;
		if (gap > 127)
			gap = 127;
	}

	*con2 = (nco << 16) | gap;
}
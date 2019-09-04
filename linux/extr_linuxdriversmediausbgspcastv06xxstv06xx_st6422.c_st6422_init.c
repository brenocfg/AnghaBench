#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int member_0; int member_1; } ;
typedef  TYPE_1__ u16 ;
struct sd {int dummy; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_1__ const**) ; 
 int STV_ISO_ENABLE ; 
 int stv06xx_write_bridge (struct sd*,TYPE_1__ const,TYPE_1__ const) ; 

__attribute__((used)) static int st6422_init(struct sd *sd)
{
	int err = 0, i;

	const u16 st6422_bridge_init[][2] = {
		{ STV_ISO_ENABLE, 0x00 }, /* disable capture */
		{ 0x1436, 0x00 },
		{ 0x1432, 0x03 },	/* 0x00-0x1F brightness */
		{ 0x143a, 0xf9 },	/* 0x00-0x0F contrast */
		{ 0x0509, 0x38 },	/* R */
		{ 0x050a, 0x38 },	/* G */
		{ 0x050b, 0x38 },	/* B */
		{ 0x050c, 0x2a },
		{ 0x050d, 0x01 },


		{ 0x1431, 0x00 },	/* 0x00-0x07 ??? */
		{ 0x1433, 0x34 },	/* 160x120, 0x00-0x01 night filter */
		{ 0x1438, 0x18 },	/* 640x480 */
/* 18 bayes */
/* 10 compressed? */

		{ 0x1439, 0x00 },
/* anti-noise?  0xa2 gives a perfect image */

		{ 0x143b, 0x05 },
		{ 0x143c, 0x00 },	/* 0x00-0x01 - ??? */


/* shutter time 0x0000-0x03FF */
/* low value  give good picures on moving objects (but requires much light) */
/* high value gives good picures in darkness (but tends to be overexposed) */
		{ 0x143e, 0x01 },
		{ 0x143d, 0x00 },

		{ 0x1442, 0xe2 },
/* write: 1x1x xxxx */
/* read:  1x1x xxxx */
/*        bit 5 == button pressed and hold if 0 */
/* write 0xe2,0xea */

/* 0x144a */
/* 0x00 init */
/* bit 7 == button has been pressed, but not handled */

/* interrupt */
/* if(urb->iso_frame_desc[i].status == 0x80) { */
/* if(urb->iso_frame_desc[i].status == 0x88) { */

		{ 0x1500, 0xd0 },
		{ 0x1500, 0xd0 },
		{ 0x1500, 0x50 },	/* 0x00 - 0xFF  0x80 == compr ? */

		{ 0x1501, 0xaf },
/* high val-> light area gets darker */
/* low val -> light area gets lighter */
		{ 0x1502, 0xc2 },
/* high val-> light area gets darker */
/* low val -> light area gets lighter */
		{ 0x1503, 0x45 },
/* high val-> light area gets darker */
/* low val -> light area gets lighter */
		{ 0x1505, 0x02 },
/* 2  : 324x248  80352 bytes */
/* 7  : 248x162  40176 bytes */
/* c+f: 162*124  20088 bytes */

		{ 0x150e, 0x8e },
		{ 0x150f, 0x37 },
		{ 0x15c0, 0x00 },
		{ 0x15c3, 0x08 },	/* 0x04/0x14 ... test pictures ??? */


		{ 0x143f, 0x01 },	/* commit settings */

	};

	for (i = 0; i < ARRAY_SIZE(st6422_bridge_init) && !err; i++) {
		err = stv06xx_write_bridge(sd, st6422_bridge_init[i][0],
					       st6422_bridge_init[i][1]);
	}

	return err;
}
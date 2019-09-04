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
struct sd {int model; } ;
struct gspca_dev {int dummy; } ;
typedef  int s32 ;

/* Variables and functions */
#define  CIT_IBM_NETCAM_PRO 133 
#define  CIT_MODEL0 132 
#define  CIT_MODEL1 131 
#define  CIT_MODEL2 130 
#define  CIT_MODEL3 129 
#define  CIT_MODEL4 128 
 int /*<<< orphan*/  cit_Packet_Format1 (struct gspca_dev*,int,int) ; 
 int /*<<< orphan*/  cit_model2_Packet1 (struct gspca_dev*,int,int) ; 
 int /*<<< orphan*/  cit_model3_Packet1 (struct gspca_dev*,int,int) ; 
 int /*<<< orphan*/  cit_model4_BrightnessPacket (struct gspca_dev*,int) ; 

__attribute__((used)) static int cit_set_brightness(struct gspca_dev *gspca_dev, s32 val)
{
	struct sd *sd = (struct sd *) gspca_dev;
	int i;

	switch (sd->model) {
	case CIT_MODEL0:
	case CIT_IBM_NETCAM_PRO:
		/* No (known) brightness control for these */
		break;
	case CIT_MODEL1:
		/* Model 1: Brightness range 0 - 63 */
		cit_Packet_Format1(gspca_dev, 0x0031, val);
		cit_Packet_Format1(gspca_dev, 0x0032, val);
		cit_Packet_Format1(gspca_dev, 0x0033, val);
		break;
	case CIT_MODEL2:
		/* Model 2: Brightness range 0x60 - 0xee */
		/* Scale 0 - 63 to 0x60 - 0xee */
		i = 0x60 + val * 2254 / 1000;
		cit_model2_Packet1(gspca_dev, 0x001a, i);
		break;
	case CIT_MODEL3:
		/* Model 3: Brightness range 'i' in [0x0C..0x3F] */
		i = val;
		if (i < 0x0c)
			i = 0x0c;
		cit_model3_Packet1(gspca_dev, 0x0036, i);
		break;
	case CIT_MODEL4:
		/* Model 4: Brightness range 'i' in [0x04..0xb4] */
		/* Scale 0 - 63 to 0x04 - 0xb4 */
		i = 0x04 + val * 2794 / 1000;
		cit_model4_BrightnessPacket(gspca_dev, i);
		break;
	}

	return 0;
}
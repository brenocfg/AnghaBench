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
 int cit_model1_ntries ; 
 int /*<<< orphan*/  cit_model3_Packet1 (struct gspca_dev*,int,unsigned short) ; 
 int /*<<< orphan*/  cit_send_FF_04_02 (struct gspca_dev*) ; 
 int /*<<< orphan*/  cit_write_reg (struct gspca_dev*,int,int) ; 

__attribute__((used)) static int cit_set_contrast(struct gspca_dev *gspca_dev, s32 val)
{
	struct sd *sd = (struct sd *) gspca_dev;

	switch (sd->model) {
	case CIT_MODEL0: {
		int i;
		/* gain 0-15, 0-20 -> 0-15 */
		i = val * 1000 / 1333;
		cit_write_reg(gspca_dev, i, 0x0422);
		/* gain 0-31, may not be lower then 0x0422, 0-20 -> 0-31 */
		i = val * 2000 / 1333;
		cit_write_reg(gspca_dev, i, 0x0423);
		/* gain 0-127, may not be lower then 0x0423, 0-20 -> 0-63  */
		i = val * 4000 / 1333;
		cit_write_reg(gspca_dev, i, 0x0424);
		/* gain 0-127, may not be lower then 0x0424, , 0-20 -> 0-127 */
		i = val * 8000 / 1333;
		cit_write_reg(gspca_dev, i, 0x0425);
		break;
	}
	case CIT_MODEL2:
	case CIT_MODEL4:
		/* These models do not have this control. */
		break;
	case CIT_MODEL1:
	{
		/* Scale 0 - 20 to 15 - 0 */
		int i, new_contrast = (20 - val) * 1000 / 1333;
		for (i = 0; i < cit_model1_ntries; i++) {
			cit_Packet_Format1(gspca_dev, 0x0014, new_contrast);
			cit_send_FF_04_02(gspca_dev);
		}
		break;
	}
	case CIT_MODEL3:
	{	/* Preset hardware values */
		static const struct {
			unsigned short cv1;
			unsigned short cv2;
			unsigned short cv3;
		} cv[7] = {
			{ 0x05, 0x05, 0x0f },	/* Minimum */
			{ 0x04, 0x04, 0x16 },
			{ 0x02, 0x03, 0x16 },
			{ 0x02, 0x08, 0x16 },
			{ 0x01, 0x0c, 0x16 },
			{ 0x01, 0x0e, 0x16 },
			{ 0x01, 0x10, 0x16 }	/* Maximum */
		};
		int i = val / 3;
		cit_model3_Packet1(gspca_dev, 0x0067, cv[i].cv1);
		cit_model3_Packet1(gspca_dev, 0x005b, cv[i].cv2);
		cit_model3_Packet1(gspca_dev, 0x005c, cv[i].cv3);
		break;
	}
	case CIT_IBM_NETCAM_PRO:
		cit_model3_Packet1(gspca_dev, 0x005b, val + 1);
		break;
	}
	return 0;
}
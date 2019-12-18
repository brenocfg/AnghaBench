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
struct sd {scalar_t__ type; int /*<<< orphan*/  freq; int /*<<< orphan*/  jpegqual; scalar_t__ blocks_left; } ;
struct TYPE_2__ {int member_0; int member_1; } ;
struct jlj_command {int member_1; int delay; scalar_t__ ack_wanted; int /*<<< orphan*/  instruction; int /*<<< orphan*/  member_2; TYPE_1__ member_0; } ;
struct gspca_dev {scalar_t__ usb_err; int /*<<< orphan*/  curr_mode; } ;

/* Variables and functions */
 int ARRAY_SIZE (struct jlj_command*) ; 
 int /*<<< orphan*/  JEILINJ_CMD_DELAY ; 
 scalar_t__ SPORTSCAM_DV15 ; 
 int SPORTSCAM_DV15_CMD_SIZE ; 
 int /*<<< orphan*/  gspca_err (struct gspca_dev*,char*) ; 
 int /*<<< orphan*/  jlj_read1 (struct gspca_dev*,int*) ; 
 int /*<<< orphan*/  jlj_write2 (struct gspca_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  setcamquality (struct gspca_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  setfreq (struct gspca_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  v4l2_ctrl_g_ctrl (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int jlj_start(struct gspca_dev *gspca_dev)
{
	int i;
	int start_commands_size;
	u8 response = 0xff;
	struct sd *sd = (struct sd *) gspca_dev;
	struct jlj_command start_commands[] = {
		{{0x71, 0x81}, 0, 0},
		{{0x70, 0x05}, 0, JEILINJ_CMD_DELAY},
		{{0x95, 0x70}, 1, 0},
		{{0x71, 0x81 - gspca_dev->curr_mode}, 0, 0},
		{{0x70, 0x04}, 0, JEILINJ_CMD_DELAY},
		{{0x95, 0x70}, 1, 0},
		{{0x71, 0x00}, 0, 0},   /* start streaming ??*/
		{{0x70, 0x08}, 0, JEILINJ_CMD_DELAY},
		{{0x95, 0x70}, 1, 0},
#define SPORTSCAM_DV15_CMD_SIZE 9
		{{0x94, 0x02}, 0, 0},
		{{0xde, 0x24}, 0, 0},
		{{0x94, 0x02}, 0, 0},
		{{0xdd, 0xf0}, 0, 0},
		{{0x94, 0x02}, 0, 0},
		{{0xe3, 0x2c}, 0, 0},
		{{0x94, 0x02}, 0, 0},
		{{0xe4, 0x00}, 0, 0},
		{{0x94, 0x02}, 0, 0},
		{{0xe5, 0x00}, 0, 0},
		{{0x94, 0x02}, 0, 0},
		{{0xe6, 0x2c}, 0, 0},
		{{0x94, 0x03}, 0, 0},
		{{0xaa, 0x00}, 0, 0}
	};

	sd->blocks_left = 0;
	/* Under Windows, USB spy shows that only the 9 first start
	 * commands are used for SPORTSCAM_DV15 webcam
	 */
	if (sd->type == SPORTSCAM_DV15)
		start_commands_size = SPORTSCAM_DV15_CMD_SIZE;
	else
		start_commands_size = ARRAY_SIZE(start_commands);

	for (i = 0; i < start_commands_size; i++) {
		jlj_write2(gspca_dev, start_commands[i].instruction);
		if (start_commands[i].delay)
			msleep(start_commands[i].delay);
		if (start_commands[i].ack_wanted)
			jlj_read1(gspca_dev, &response);
	}
	setcamquality(gspca_dev, v4l2_ctrl_g_ctrl(sd->jpegqual));
	msleep(2);
	setfreq(gspca_dev, v4l2_ctrl_g_ctrl(sd->freq));
	if (gspca_dev->usb_err < 0)
		gspca_err(gspca_dev, "Start streaming command failed\n");
	return gspca_dev->usb_err;
}
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
struct sd {int model; } ;
struct TYPE_2__ {int member_0; int member_1; int member_2; int member_3; int member_4; int member_5; } ;
struct init_command {int /*<<< orphan*/ * instruction; int /*<<< orphan*/  member_1; TYPE_1__ member_0; } ;
struct gspca_dev {int /*<<< orphan*/  streaming; } ;
typedef  int /*<<< orphan*/  s32 ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (struct init_command*) ; 
 int /*<<< orphan*/  run_start_commands (struct gspca_dev*,struct init_command*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void set_gain(struct gspca_dev *gspca_dev, s32 g)
{
	struct sd *sd = (struct sd *) gspca_dev;

	struct init_command genius_vcam_live_gain_cmds[] = {
		{{0x1d, 0x25, 0x10 /* This byte is gain */,
		  0x20, 0xab, 0x00}, 0},
	};
	if (!gspca_dev->streaming)
		return;

	switch (sd->model) {
	case 0x7003:
		genius_vcam_live_gain_cmds[0].instruction[2] = g;
		run_start_commands(gspca_dev, genius_vcam_live_gain_cmds,
				   ARRAY_SIZE(genius_vcam_live_gain_cmds));
		break;
	default:
		break;
	}
}
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
struct sd {int resetlevel_frame_count; int resetlevel; int resetlevel_adjust_dir; scalar_t__ restart_stream; } ;
struct gspca_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  HV7131_REG_ARLV ; 
 int /*<<< orphan*/  HV7131_REG_HIREFNOH ; 
 int /*<<< orphan*/  HV7131_REG_HIREFNOL ; 
 int /*<<< orphan*/  HV7131_REG_LOREFNOH ; 
 int /*<<< orphan*/  HV7131_REG_LOREFNOL ; 
 int /*<<< orphan*/  sd_start (struct gspca_dev*) ; 
 int /*<<< orphan*/  sd_stopN (struct gspca_dev*) ; 
 int se401_get_feature (struct gspca_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  se401_set_feature (struct gspca_dev*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void sd_dq_callback(struct gspca_dev *gspca_dev)
{
	struct sd *sd = (struct sd *)gspca_dev;
	unsigned int ahrc, alrc;
	int oldreset, adjust_dir;

	/* Restart the stream if requested do so by pkt_scan */
	if (sd->restart_stream) {
		sd_stopN(gspca_dev);
		sd_start(gspca_dev);
		sd->restart_stream = 0;
	}

	/* Automatically adjust sensor reset level
	   Hyundai have some really nice docs about this and other sensor
	   related stuff on their homepage: www.hei.co.kr */
	sd->resetlevel_frame_count++;
	if (sd->resetlevel_frame_count < 20)
		return;

	/* For some reason this normally read-only register doesn't get reset
	   to zero after reading them just once... */
	se401_get_feature(gspca_dev, HV7131_REG_HIREFNOH);
	se401_get_feature(gspca_dev, HV7131_REG_HIREFNOL);
	se401_get_feature(gspca_dev, HV7131_REG_LOREFNOH);
	se401_get_feature(gspca_dev, HV7131_REG_LOREFNOL);
	ahrc = 256*se401_get_feature(gspca_dev, HV7131_REG_HIREFNOH) +
	    se401_get_feature(gspca_dev, HV7131_REG_HIREFNOL);
	alrc = 256*se401_get_feature(gspca_dev, HV7131_REG_LOREFNOH) +
	    se401_get_feature(gspca_dev, HV7131_REG_LOREFNOL);

	/* Not an exact science, but it seems to work pretty well... */
	oldreset = sd->resetlevel;
	if (alrc > 10) {
		while (alrc >= 10 && sd->resetlevel < 63) {
			sd->resetlevel++;
			alrc /= 2;
		}
	} else if (ahrc > 20) {
		while (ahrc >= 20 && sd->resetlevel > 0) {
			sd->resetlevel--;
			ahrc /= 2;
		}
	}
	/* Detect ping-pong-ing and halve adjustment to avoid overshoot */
	if (sd->resetlevel > oldreset)
		adjust_dir = 1;
	else
		adjust_dir = -1;
	if (sd->resetlevel_adjust_dir &&
	    sd->resetlevel_adjust_dir != adjust_dir)
		sd->resetlevel = oldreset + (sd->resetlevel - oldreset) / 2;

	if (sd->resetlevel != oldreset) {
		sd->resetlevel_adjust_dir = adjust_dir;
		se401_set_feature(gspca_dev, HV7131_REG_ARLV, sd->resetlevel);
	}

	sd->resetlevel_frame_count = 0;
}
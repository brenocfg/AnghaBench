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
typedef  int u32 ;
typedef  int u16 ;
struct gspca_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  D_STREAM ; 
 int GAIN_MAX ; 
 int /*<<< orphan*/  REG_BLUE_GAIN ; 
 int gainify (int) ; 
 int /*<<< orphan*/  gspca_dbg (struct gspca_dev*,int /*<<< orphan*/ ,char*,int,int,...) ; 
 int /*<<< orphan*/  reg_w (struct gspca_dev*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void setbgain(struct gspca_dev *gspca_dev,
		u16 gain, u16 global_gain)
{
	u16 normalized;

	normalized = global_gain +
		((u32)global_gain) * gain / GAIN_MAX;
	if (normalized > GAIN_MAX) {
		gspca_dbg(gspca_dev, D_STREAM, "Truncating blue 0x%04X w/ value 0x%04X\n\n",
			  GAIN_MAX, normalized);
		normalized = GAIN_MAX;
	}
	normalized = gainify(normalized);
	gspca_dbg(gspca_dev, D_STREAM, "gain B (0x%04X): 0x%04X w/ source 0x%04X\n\n",
		  REG_BLUE_GAIN, normalized, gain);

	reg_w(gspca_dev, normalized, REG_BLUE_GAIN);
}
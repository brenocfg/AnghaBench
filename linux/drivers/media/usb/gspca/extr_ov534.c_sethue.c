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
typedef  int u8 ;
struct sd {scalar_t__ sensor; } ;
struct gspca_dev {int dummy; } ;
typedef  int /*<<< orphan*/  s32 ;
typedef  int s16 ;

/* Variables and functions */
 scalar_t__ SENSOR_OV767x ; 
 int fixp_cos16 (int /*<<< orphan*/ ) ; 
 int fixp_sin16 (int /*<<< orphan*/ ) ; 
 int sccb_reg_read (struct gspca_dev*,int) ; 
 int /*<<< orphan*/  sccb_reg_write (struct gspca_dev*,int,int) ; 

__attribute__((used)) static void sethue(struct gspca_dev *gspca_dev, s32 val)
{
	struct sd *sd = (struct sd *) gspca_dev;

	if (sd->sensor == SENSOR_OV767x) {
		/* TBD */
	} else {
		s16 huesin;
		s16 huecos;

		/* According to the datasheet the registers expect HUESIN and
		 * HUECOS to be the result of the trigonometric functions,
		 * scaled by 0x80.
		 *
		 * The 0x7fff here represents the maximum absolute value
		 * returned byt fixp_sin and fixp_cos, so the scaling will
		 * consider the result like in the interval [-1.0, 1.0].
		 */
		huesin = fixp_sin16(val) * 0x80 / 0x7fff;
		huecos = fixp_cos16(val) * 0x80 / 0x7fff;

		if (huesin < 0) {
			sccb_reg_write(gspca_dev, 0xab,
				sccb_reg_read(gspca_dev, 0xab) | 0x2);
			huesin = -huesin;
		} else {
			sccb_reg_write(gspca_dev, 0xab,
				sccb_reg_read(gspca_dev, 0xab) & ~0x2);

		}
		sccb_reg_write(gspca_dev, 0xa9, (u8)huecos);
		sccb_reg_write(gspca_dev, 0xaa, (u8)huesin);
	}
}
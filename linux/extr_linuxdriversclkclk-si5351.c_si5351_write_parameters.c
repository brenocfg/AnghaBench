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
struct si5351_parameters {int p1; int p3; int p2; } ;
struct si5351_driver_data {int dummy; } ;

/* Variables and functions */
#define  SI5351_CLK6_PARAMETERS 129 
#define  SI5351_CLK7_PARAMETERS 128 
 int SI5351_PARAMETERS_LENGTH ; 
 int /*<<< orphan*/  si5351_bulk_write (struct si5351_driver_data*,int,int,int*) ; 
 int si5351_reg_read (struct si5351_driver_data*,int) ; 
 int /*<<< orphan*/  si5351_reg_write (struct si5351_driver_data*,int,int) ; 

__attribute__((used)) static void si5351_write_parameters(struct si5351_driver_data *drvdata,
				    u8 reg, struct si5351_parameters *params)
{
	u8 buf[SI5351_PARAMETERS_LENGTH];

	switch (reg) {
	case SI5351_CLK6_PARAMETERS:
	case SI5351_CLK7_PARAMETERS:
		buf[0] = params->p1 & 0xff;
		si5351_reg_write(drvdata, reg, buf[0]);
		break;
	default:
		buf[0] = ((params->p3 & 0x0ff00) >> 8) & 0xff;
		buf[1] = params->p3 & 0xff;
		/* save rdiv and divby4 */
		buf[2] = si5351_reg_read(drvdata, reg + 2) & ~0x03;
		buf[2] |= ((params->p1 & 0x30000) >> 16) & 0x03;
		buf[3] = ((params->p1 & 0x0ff00) >> 8) & 0xff;
		buf[4] = params->p1 & 0xff;
		buf[5] = ((params->p3 & 0xf0000) >> 12) |
			((params->p2 & 0xf0000) >> 16);
		buf[6] = ((params->p2 & 0x0ff00) >> 8) & 0xff;
		buf[7] = params->p2 & 0xff;
		si5351_bulk_write(drvdata, reg, SI5351_PARAMETERS_LENGTH, buf);
	}
}
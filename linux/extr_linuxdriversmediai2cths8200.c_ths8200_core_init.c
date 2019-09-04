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
struct v4l2_subdev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  THS8200_CHIP_CTL ; 
 int /*<<< orphan*/  THS8200_DATA_CNTL ; 
 int /*<<< orphan*/  THS8200_DTG1_CBCR_SYNC_MSB ; 
 int /*<<< orphan*/  THS8200_DTG1_MODE ; 
 int /*<<< orphan*/  THS8200_DTG1_Y_SYNC_MSB ; 
 int /*<<< orphan*/  ths8200_write (struct v4l2_subdev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ths8200_write_and_or (struct v4l2_subdev*,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void ths8200_core_init(struct v4l2_subdev *sd)
{
	/* setup clocks */
	ths8200_write_and_or(sd, THS8200_CHIP_CTL, 0x3f, 0xc0);

	/**** Data path control (DATA) ****/
	/* Set FSADJ 700 mV,
	 * bypass 422-444 interpolation,
	 * input format 30 bit RGB444
	 */
	ths8200_write(sd, THS8200_DATA_CNTL, 0x70);

	/* DTG Mode (Video blocked during blanking
	 * VESA slave
	 */
	ths8200_write(sd, THS8200_DTG1_MODE, 0x87);

	/**** Display Timing Generator Control, Part 1 (DTG1). ****/

	/* Disable embedded syncs on the output by setting
	 * the amplitude to zero for all channels.
	 */
	ths8200_write(sd, THS8200_DTG1_Y_SYNC_MSB, 0x00);
	ths8200_write(sd, THS8200_DTG1_CBCR_SYNC_MSB, 0x00);
}
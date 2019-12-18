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
struct stv0900_internal {int chip_id; } ;
typedef  int s32 ;
typedef  enum fe_stv0900_demod_num { ____Placeholder_fe_stv0900_demod_num } fe_stv0900_demod_num ;

/* Variables and functions */
 int /*<<< orphan*/  MANUALS2_ROLLOFF ; 
 int /*<<< orphan*/  MANUALSX_ROLLOFF ; 
 int /*<<< orphan*/  MATSTR1 ; 
 int /*<<< orphan*/  ROLLOFF_CONTROL ; 
 int stv0900_read_reg (struct stv0900_internal*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stv0900_write_bits (struct stv0900_internal*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void stv0900_set_dvbs2_rolloff(struct stv0900_internal *intp,
					enum fe_stv0900_demod_num demod)
{
	s32 rolloff;

	if (intp->chip_id == 0x10) {
		stv0900_write_bits(intp, MANUALSX_ROLLOFF, 1);
		rolloff = stv0900_read_reg(intp, MATSTR1) & 0x03;
		stv0900_write_bits(intp, ROLLOFF_CONTROL, rolloff);
	} else if (intp->chip_id <= 0x20)
		stv0900_write_bits(intp, MANUALSX_ROLLOFF, 0);
	else /* cut 3.0 */
		stv0900_write_bits(intp, MANUALS2_ROLLOFF, 0);
}
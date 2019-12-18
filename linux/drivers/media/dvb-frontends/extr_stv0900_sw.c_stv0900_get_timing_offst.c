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
typedef  scalar_t__ u32 ;
struct stv0900_internal {int dummy; } ;
typedef  int s32 ;
typedef  enum fe_stv0900_demod_num { ____Placeholder_fe_stv0900_demod_num } fe_stv0900_demod_num ;

/* Variables and functions */
 scalar_t__ TMGREG2 ; 
 int ge2comp (int,int) ; 
 int stv0900_read_reg (struct stv0900_internal*,scalar_t__) ; 

__attribute__((used)) static s32 stv0900_get_timing_offst(struct stv0900_internal *intp,
					u32 srate,
					enum fe_stv0900_demod_num demod)
{
	s32 timingoffset;


	timingoffset = (stv0900_read_reg(intp, TMGREG2) << 16) +
		       (stv0900_read_reg(intp, TMGREG2 + 1) << 8) +
		       (stv0900_read_reg(intp, TMGREG2 + 2));

	timingoffset = ge2comp(timingoffset, 24);


	if (timingoffset == 0)
		timingoffset = 1;

	timingoffset = ((s32)srate * 10) / ((s32)0x1000000 / timingoffset);
	timingoffset /= 320;

	return timingoffset;
}
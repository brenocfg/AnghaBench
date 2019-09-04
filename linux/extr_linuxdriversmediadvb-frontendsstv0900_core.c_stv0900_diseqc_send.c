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
typedef  int /*<<< orphan*/  u8 ;
typedef  size_t u32 ;
struct stv0900_internal {int dummy; } ;
typedef  size_t s32 ;
typedef  enum fe_stv0900_demod_num { ____Placeholder_fe_stv0900_demod_num } fe_stv0900_demod_num ;

/* Variables and functions */
 int /*<<< orphan*/  DISTXDATA ; 
 int /*<<< orphan*/  DIS_PRECHARGE ; 
 int /*<<< orphan*/  FIFO_FULL ; 
 int /*<<< orphan*/  TX_IDLE ; 
 int /*<<< orphan*/  msleep (int) ; 
 int stv0900_get_bits (struct stv0900_internal*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stv0900_write_bits (struct stv0900_internal*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stv0900_write_reg (struct stv0900_internal*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int stv0900_diseqc_send(struct stv0900_internal *intp , u8 *data,
				u32 NbData, enum fe_stv0900_demod_num demod)
{
	s32 i = 0;

	stv0900_write_bits(intp, DIS_PRECHARGE, 1);
	while (i < NbData) {
		while (stv0900_get_bits(intp, FIFO_FULL))
			;/* checkpatch complains */
		stv0900_write_reg(intp, DISTXDATA, data[i]);
		i++;
	}

	stv0900_write_bits(intp, DIS_PRECHARGE, 0);
	i = 0;
	while ((stv0900_get_bits(intp, TX_IDLE) != 1) && (i < 10)) {
		msleep(10);
		i++;
	}

	return 0;
}
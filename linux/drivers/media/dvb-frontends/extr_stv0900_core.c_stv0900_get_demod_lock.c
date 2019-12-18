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
struct stv0900_internal {int dummy; } ;
typedef  scalar_t__ s32 ;
typedef  enum fe_stv0900_search_state { ____Placeholder_fe_stv0900_search_state } fe_stv0900_search_state ;
typedef  enum fe_stv0900_demod_num { ____Placeholder_fe_stv0900_demod_num } fe_stv0900_demod_num ;

/* Variables and functions */
 int /*<<< orphan*/  HEADER_MODE ; 
 int /*<<< orphan*/  LOCK_DEFINITIF ; 
#define  STV0900_DVBS2_FOUND 131 
#define  STV0900_DVBS_FOUND 130 
#define  STV0900_PLH_DETECTED 129 
#define  STV0900_SEARCH 128 
 int /*<<< orphan*/  dprintk (char*,...) ; 
 int /*<<< orphan*/  msleep (int) ; 
 void* stv0900_get_bits (struct stv0900_internal*,int /*<<< orphan*/ ) ; 

int stv0900_get_demod_lock(struct stv0900_internal *intp,
			enum fe_stv0900_demod_num demod, s32 time_out)
{
	s32 timer = 0,
		lock = 0;

	enum fe_stv0900_search_state	dmd_state;

	while ((timer < time_out) && (lock == 0)) {
		dmd_state = stv0900_get_bits(intp, HEADER_MODE);
		dprintk("Demod State = %d\n", dmd_state);
		switch (dmd_state) {
		case STV0900_SEARCH:
		case STV0900_PLH_DETECTED:
		default:
			lock = 0;
			break;
		case STV0900_DVBS2_FOUND:
		case STV0900_DVBS_FOUND:
			lock = stv0900_get_bits(intp, LOCK_DEFINITIF);
			break;
		}

		if (lock == 0)
			msleep(10);

		timer += 10;
	}

	if (lock)
		dprintk("DEMOD LOCK OK\n");
	else
		dprintk("DEMOD LOCK FAIL\n");

	return lock;
}
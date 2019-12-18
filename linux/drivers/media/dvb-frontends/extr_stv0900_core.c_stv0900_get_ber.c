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
struct stv0900_internal {int dummy; } ;
typedef  int s32 ;
typedef  enum fe_stv0900_demod_num { ____Placeholder_fe_stv0900_demod_num } fe_stv0900_demod_num ;

/* Variables and functions */
 int /*<<< orphan*/  HEADER_MODE ; 
 int /*<<< orphan*/  PKTDELIN_LOCK ; 
 int /*<<< orphan*/  PRFVIT ; 
#define  STV0900_DVBS2_FOUND 131 
#define  STV0900_DVBS_FOUND 130 
#define  STV0900_PLH_DETECTED 129 
#define  STV0900_SEARCH 128 
 int /*<<< orphan*/  msleep (int) ; 
 int stv0900_get_bits (struct stv0900_internal*,int /*<<< orphan*/ ) ; 
 int stv0900_get_err_count (struct stv0900_internal*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static u32 stv0900_get_ber(struct stv0900_internal *intp,
				enum fe_stv0900_demod_num demod)
{
	u32 ber = 10000000, i;
	s32 demod_state;

	demod_state = stv0900_get_bits(intp, HEADER_MODE);

	switch (demod_state) {
	case STV0900_SEARCH:
	case STV0900_PLH_DETECTED:
	default:
		ber = 10000000;
		break;
	case STV0900_DVBS_FOUND:
		ber = 0;
		for (i = 0; i < 5; i++) {
			msleep(5);
			ber += stv0900_get_err_count(intp, 0, demod);
		}

		ber /= 5;
		if (stv0900_get_bits(intp, PRFVIT)) {
			ber *= 9766;
			ber = ber >> 13;
		}

		break;
	case STV0900_DVBS2_FOUND:
		ber = 0;
		for (i = 0; i < 5; i++) {
			msleep(5);
			ber += stv0900_get_err_count(intp, 0, demod);
		}

		ber /= 5;
		if (stv0900_get_bits(intp, PKTDELIN_LOCK)) {
			ber *= 9766;
			ber = ber >> 13;
		}

		break;
	}

	return ber;
}
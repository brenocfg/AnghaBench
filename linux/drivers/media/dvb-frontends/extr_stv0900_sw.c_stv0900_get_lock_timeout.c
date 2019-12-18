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
typedef  int s32 ;
typedef  enum fe_stv0900_search_algo { ____Placeholder_fe_stv0900_search_algo } fe_stv0900_search_algo ;

/* Variables and functions */
#define  STV0900_BLIND_SEARCH 130 
#define  STV0900_COLD_START 129 
#define  STV0900_WARM_START 128 

__attribute__((used)) static void stv0900_get_lock_timeout(s32 *demod_timeout, s32 *fec_timeout,
					s32 srate,
					enum fe_stv0900_search_algo algo)
{
	switch (algo) {
	case STV0900_BLIND_SEARCH:
		if (srate <= 1500000) {
			(*demod_timeout) = 1500;
			(*fec_timeout) = 400;
		} else if (srate <= 5000000) {
			(*demod_timeout) = 1000;
			(*fec_timeout) = 300;
		} else {
			(*demod_timeout) = 700;
			(*fec_timeout) = 100;
		}

		break;
	case STV0900_COLD_START:
	case STV0900_WARM_START:
	default:
		if (srate <= 1000000) {
			(*demod_timeout) = 3000;
			(*fec_timeout) = 1700;
		} else if (srate <= 2000000) {
			(*demod_timeout) = 2500;
			(*fec_timeout) = 1100;
		} else if (srate <= 5000000) {
			(*demod_timeout) = 1000;
			(*fec_timeout) = 550;
		} else if (srate <= 10000000) {
			(*demod_timeout) = 700;
			(*fec_timeout) = 250;
		} else if (srate <= 20000000) {
			(*demod_timeout) = 400;
			(*fec_timeout) = 130;
		} else {
			(*demod_timeout) = 300;
			(*fec_timeout) = 100;
		}

		break;

	}

	if (algo == STV0900_WARM_START)
		(*demod_timeout) /= 2;
}
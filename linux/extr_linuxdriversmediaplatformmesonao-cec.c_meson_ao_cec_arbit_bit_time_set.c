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
struct meson_ao_cec_device {int dummy; } ;

/* Variables and functions */
#define  CEC_SIGNAL_FREE_TIME_NEW_INITIATOR 130 
#define  CEC_SIGNAL_FREE_TIME_NEXT_XFER 129 
#define  CEC_SIGNAL_FREE_TIME_RETRY 128 
 int /*<<< orphan*/  CEC_TXTIME_17MS_BIT10_8 ; 
 int /*<<< orphan*/  CEC_TXTIME_17MS_BIT7_0 ; 
 int /*<<< orphan*/  CEC_TXTIME_2BIT_BIT10_8 ; 
 int /*<<< orphan*/  CEC_TXTIME_2BIT_BIT7_0 ; 
 int /*<<< orphan*/  CEC_TXTIME_4BIT_BIT10_8 ; 
 int /*<<< orphan*/  CEC_TXTIME_4BIT_BIT7_0 ; 
 int /*<<< orphan*/  meson_ao_cec_write (struct meson_ao_cec_device*,int /*<<< orphan*/ ,unsigned int,int*) ; 

__attribute__((used)) static int meson_ao_cec_arbit_bit_time_set(struct meson_ao_cec_device *ao_cec,
					   unsigned int bit_set,
					   unsigned int time_set)
{
	int ret = 0;

	switch (bit_set) {
	case CEC_SIGNAL_FREE_TIME_RETRY:
		meson_ao_cec_write(ao_cec, CEC_TXTIME_4BIT_BIT7_0,
				   time_set & 0xff, &ret);
		meson_ao_cec_write(ao_cec, CEC_TXTIME_4BIT_BIT10_8,
				   (time_set >> 8) & 0x7, &ret);
		break;

	case CEC_SIGNAL_FREE_TIME_NEW_INITIATOR:
		meson_ao_cec_write(ao_cec, CEC_TXTIME_2BIT_BIT7_0,
				   time_set & 0xff, &ret);
		meson_ao_cec_write(ao_cec, CEC_TXTIME_2BIT_BIT10_8,
				   (time_set >> 8) & 0x7, &ret);
		break;

	case CEC_SIGNAL_FREE_TIME_NEXT_XFER:
		meson_ao_cec_write(ao_cec, CEC_TXTIME_17MS_BIT7_0,
				   time_set & 0xff, &ret);
		meson_ao_cec_write(ao_cec, CEC_TXTIME_17MS_BIT10_8,
				   (time_set >> 8) & 0x7, &ret);
		break;
	}

	return ret;
}
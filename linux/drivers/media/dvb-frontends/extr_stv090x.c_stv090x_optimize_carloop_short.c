#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct stv090x_state {int modulation; int srate; TYPE_1__* internal; } ;
struct stv090x_short_frame_crloop {int crl_2; int crl_5; int crl_10; int crl_20; int crl_30; } ;
typedef  size_t s32 ;
struct TYPE_2__ {int dev_ver; } ;

/* Variables and functions */
#define  STV090x_16APSK 131 
#define  STV090x_32APSK 130 
#define  STV090x_8PSK 129 
#define  STV090x_QPSK 128 
 struct stv090x_short_frame_crloop* stv090x_s2_short_crl_cut20 ; 
 struct stv090x_short_frame_crloop* stv090x_s2_short_crl_cut30 ; 

__attribute__((used)) static u8 stv090x_optimize_carloop_short(struct stv090x_state *state)
{
	struct stv090x_short_frame_crloop *short_crl = NULL;
	s32 index = 0;
	u8 aclc = 0x0b;

	switch (state->modulation) {
	case STV090x_QPSK:
	default:
		index = 0;
		break;
	case STV090x_8PSK:
		index = 1;
		break;
	case STV090x_16APSK:
		index = 2;
		break;
	case STV090x_32APSK:
		index = 3;
		break;
	}

	if (state->internal->dev_ver >= 0x30) {
		/* Cut 3.0 and up */
		short_crl = stv090x_s2_short_crl_cut30;
	} else {
		/* Cut 2.0 and up: we don't support cuts older than 2.0 */
		short_crl = stv090x_s2_short_crl_cut20;
	}

	if (state->srate <= 3000000)
		aclc = short_crl[index].crl_2;
	else if (state->srate <= 7000000)
		aclc = short_crl[index].crl_5;
	else if (state->srate <= 15000000)
		aclc = short_crl[index].crl_10;
	else if (state->srate <= 25000000)
		aclc = short_crl[index].crl_20;
	else
		aclc = short_crl[index].crl_30;

	return aclc;
}
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
typedef  int u16 ;
struct dib8000_state {int dummy; } ;

/* Variables and functions */
#define  QAM_16 129 
#define  QAM_64 128 
 int* adp_Q16 ; 
 int* adp_Q64 ; 
 int* adp_Qdefault ; 
 int /*<<< orphan*/  dib8000_write_word (struct dib8000_state*,int,int const) ; 

__attribute__((used)) static u16 dib8000_adp_fine_tune(struct dib8000_state *state, u16 max_constellation)
{
	u16 i, ana_gain = 0;
	const u16 *adp;

	/* channel estimation fine configuration */
	switch (max_constellation) {
	case QAM_64:
			ana_gain = 0x7;
			adp = &adp_Q64[0];
			break;
	case QAM_16:
			ana_gain = 0x7;
			adp = &adp_Q16[0];
			break;
	default:
			ana_gain = 0;
			adp = &adp_Qdefault[0];
			break;
	}

	for (i = 0; i < 4; i++)
		dib8000_write_word(state, 215 + i, adp[i]);

	return ana_gain;
}
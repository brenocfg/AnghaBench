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
typedef  int u8 ;
struct mt312_state {int dummy; } ;
typedef  enum fe_code_rate { ____Placeholder_fe_code_rate } fe_code_rate ;

/* Variables and functions */
 int const FEC_1_2 ; 
 int const FEC_2_3 ; 
 int const FEC_3_4 ; 
 int const FEC_5_6 ; 
 int const FEC_6_7 ; 
 int const FEC_7_8 ; 
 int const FEC_AUTO ; 
 int /*<<< orphan*/  FEC_STATUS ; 
 int mt312_readreg (struct mt312_state*,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static int mt312_get_code_rate(struct mt312_state *state, enum fe_code_rate *cr)
{
	const enum fe_code_rate fec_tab[8] =
	    { FEC_1_2, FEC_2_3, FEC_3_4, FEC_5_6, FEC_6_7, FEC_7_8,
		FEC_AUTO, FEC_AUTO };

	int ret;
	u8 fec_status;

	ret = mt312_readreg(state, FEC_STATUS, &fec_status);
	if (ret < 0)
		return ret;

	*cr = fec_tab[(fec_status >> 4) & 0x07];

	return 0;
}
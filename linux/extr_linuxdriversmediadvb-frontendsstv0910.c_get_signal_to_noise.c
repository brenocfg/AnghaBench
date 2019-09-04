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
typedef  scalar_t__ u8 ;
typedef  int u16 ;
struct stv {scalar_t__ receive_mode; scalar_t__ regoff; int /*<<< orphan*/  started; } ;
struct slookup {int dummy; } ;
typedef  int /*<<< orphan*/  s32 ;

/* Variables and functions */
 int ARRAY_SIZE (struct slookup*) ; 
 int EINVAL ; 
 scalar_t__ RCVMODE_DVBS2 ; 
 scalar_t__ RSTV0910_P2_NNOSDATAT0 ; 
 scalar_t__ RSTV0910_P2_NNOSDATAT1 ; 
 scalar_t__ RSTV0910_P2_NNOSPLHT0 ; 
 scalar_t__ RSTV0910_P2_NNOSPLHT1 ; 
 int /*<<< orphan*/  read_reg (struct stv*,scalar_t__,scalar_t__*) ; 
 struct slookup* s1_sn_lookup ; 
 struct slookup* s2_sn_lookup ; 
 int /*<<< orphan*/  table_lookup (struct slookup const*,int,int) ; 

__attribute__((used)) static int get_signal_to_noise(struct stv *state, s32 *signal_to_noise)
{
	u8 data0;
	u8 data1;
	u16 data;
	int n_lookup;
	const struct slookup *lookup;

	*signal_to_noise = 0;

	if (!state->started)
		return -EINVAL;

	if (state->receive_mode == RCVMODE_DVBS2) {
		read_reg(state, RSTV0910_P2_NNOSPLHT1 + state->regoff,
			 &data1);
		read_reg(state, RSTV0910_P2_NNOSPLHT0 + state->regoff,
			 &data0);
		n_lookup = ARRAY_SIZE(s2_sn_lookup);
		lookup = s2_sn_lookup;
	} else {
		read_reg(state, RSTV0910_P2_NNOSDATAT1 + state->regoff,
			 &data1);
		read_reg(state, RSTV0910_P2_NNOSDATAT0 + state->regoff,
			 &data0);
		n_lookup = ARRAY_SIZE(s1_sn_lookup);
		lookup = s1_sn_lookup;
	}
	data = (((u16)data1) << 8) | (u16)data0;
	*signal_to_noise = table_lookup(lookup, n_lookup, data);
	return 0;
}
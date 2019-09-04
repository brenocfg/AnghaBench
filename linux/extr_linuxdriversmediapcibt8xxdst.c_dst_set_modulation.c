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
struct dst_state {scalar_t__ dst_type; int modulation; int* tx_tuna; int /*<<< orphan*/  fw_name; } ;
typedef  enum fe_modulation { ____Placeholder_fe_modulation } fe_modulation ;

/* Variables and functions */
 scalar_t__ DST_TYPE_IS_CABLE ; 
 int EINVAL ; 
 int EOPNOTSUPP ; 
#define  QAM_128 136 
#define  QAM_16 135 
#define  QAM_256 134 
#define  QAM_32 133 
#define  QAM_64 132 
#define  QAM_AUTO 131 
#define  QPSK 130 
#define  VSB_16 129 
#define  VSB_8 128 
 int /*<<< orphan*/  strncmp (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static int dst_set_modulation(struct dst_state *state,
			      enum fe_modulation modulation)
{
	if (state->dst_type != DST_TYPE_IS_CABLE)
		return -EOPNOTSUPP;

	state->modulation = modulation;
	switch (modulation) {
	case QAM_16:
		state->tx_tuna[8] = 0x10;
		break;
	case QAM_32:
		state->tx_tuna[8] = 0x20;
		break;
	case QAM_64:
		state->tx_tuna[8] = 0x40;
		break;
	case QAM_128:
		state->tx_tuna[8] = 0x80;
		break;
	case QAM_256:
		if (!strncmp(state->fw_name, "DCTNEW", 6))
			state->tx_tuna[8] = 0xff;
		else if (!strncmp(state->fw_name, "DCT-CI", 6))
			state->tx_tuna[8] = 0x00;
		break;
	case QPSK:
	case QAM_AUTO:
	case VSB_8:
	case VSB_16:
	default:
		return -EINVAL;

	}

	return 0;
}
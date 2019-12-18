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
struct r8152 {int version; } ;

/* Variables and functions */
 int CR_RE ; 
 int CR_TE ; 
 int /*<<< orphan*/  MCU_TYPE_PLA ; 
 int /*<<< orphan*/  PLA_CR ; 
#define  RTL_VER_08 129 
#define  RTL_VER_09 128 
 int ocp_read_byte (struct r8152*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocp_write_byte (struct r8152*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  r8152b_reset_packet_filter (struct r8152*) ; 
 int /*<<< orphan*/  r8153b_rx_agg_chg_indicate (struct r8152*) ; 
 int /*<<< orphan*/  rxdy_gated_en (struct r8152*,int) ; 

__attribute__((used)) static int rtl_enable(struct r8152 *tp)
{
	u32 ocp_data;

	r8152b_reset_packet_filter(tp);

	ocp_data = ocp_read_byte(tp, MCU_TYPE_PLA, PLA_CR);
	ocp_data |= CR_RE | CR_TE;
	ocp_write_byte(tp, MCU_TYPE_PLA, PLA_CR, ocp_data);

	switch (tp->version) {
	case RTL_VER_08:
	case RTL_VER_09:
		r8153b_rx_agg_chg_indicate(tp);
		break;
	default:
		break;
	}

	rxdy_gated_en(tp, false);

	return 0;
}
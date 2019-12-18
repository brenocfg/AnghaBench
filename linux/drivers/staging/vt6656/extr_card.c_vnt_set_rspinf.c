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
typedef  int /*<<< orphan*/  u16 ;
struct vnt_private {int dummy; } ;
struct vnt_phy_field {scalar_t__ service; scalar_t__ signal; int /*<<< orphan*/  len; } ;

/* Variables and functions */
 int /*<<< orphan*/  MAC_REG_RSPINF_B_1 ; 
 int /*<<< orphan*/  MESSAGE_REQUEST_MACREG ; 
 int /*<<< orphan*/  MESSAGE_TYPE_WRITE ; 
 int /*<<< orphan*/  PK_TYPE_11B ; 
 int /*<<< orphan*/  RATE_11M ; 
 int /*<<< orphan*/  RATE_12M ; 
 int /*<<< orphan*/  RATE_18M ; 
 int /*<<< orphan*/  RATE_1M ; 
 int /*<<< orphan*/  RATE_24M ; 
 int /*<<< orphan*/  RATE_2M ; 
 int /*<<< orphan*/  RATE_36M ; 
 int /*<<< orphan*/  RATE_48M ; 
 int /*<<< orphan*/  RATE_54M ; 
 int /*<<< orphan*/  RATE_5M ; 
 int /*<<< orphan*/  RATE_6M ; 
 int /*<<< orphan*/  RATE_9M ; 
 int /*<<< orphan*/  put_unaligned (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vnt_calculate_ofdm_rate (int /*<<< orphan*/ ,scalar_t__,scalar_t__*,scalar_t__*) ; 
 int /*<<< orphan*/  vnt_control_out (struct vnt_private*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,scalar_t__*) ; 
 int /*<<< orphan*/  vnt_get_cck_rate (struct vnt_private*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vnt_get_ofdm_rate (struct vnt_private*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vnt_get_phy_field (struct vnt_private*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct vnt_phy_field*) ; 

void vnt_set_rspinf(struct vnt_private *priv, u8 bb_type)
{
	struct vnt_phy_field phy[4];
	u8 tx_rate[9] = {0, 0, 0, 0, 0, 0, 0, 0, 0}; /* For OFDM */
	u8 rsv_time[9] = {0, 0, 0, 0, 0, 0, 0, 0, 0};
	u8 data[34];
	int i;

	/*RSPINF_b_1*/
	vnt_get_phy_field(priv, 14, vnt_get_cck_rate(priv, RATE_1M),
			  PK_TYPE_11B, &phy[0]);

	/*RSPINF_b_2*/
	vnt_get_phy_field(priv, 14, vnt_get_cck_rate(priv, RATE_2M),
			  PK_TYPE_11B, &phy[1]);

	/*RSPINF_b_5*/
	vnt_get_phy_field(priv, 14, vnt_get_cck_rate(priv, RATE_5M),
			  PK_TYPE_11B, &phy[2]);

	/*RSPINF_b_11*/
	vnt_get_phy_field(priv, 14, vnt_get_cck_rate(priv, RATE_11M),
			  PK_TYPE_11B, &phy[3]);

	/*RSPINF_a_6*/
	vnt_calculate_ofdm_rate(RATE_6M, bb_type, &tx_rate[0], &rsv_time[0]);

	/*RSPINF_a_9*/
	vnt_calculate_ofdm_rate(RATE_9M, bb_type, &tx_rate[1], &rsv_time[1]);

	/*RSPINF_a_12*/
	vnt_calculate_ofdm_rate(RATE_12M, bb_type, &tx_rate[2], &rsv_time[2]);

	/*RSPINF_a_18*/
	vnt_calculate_ofdm_rate(RATE_18M, bb_type, &tx_rate[3], &rsv_time[3]);

	/*RSPINF_a_24*/
	vnt_calculate_ofdm_rate(RATE_24M, bb_type, &tx_rate[4], &rsv_time[4]);

	/*RSPINF_a_36*/
	vnt_calculate_ofdm_rate(vnt_get_ofdm_rate(priv, RATE_36M),
				bb_type, &tx_rate[5], &rsv_time[5]);

	/*RSPINF_a_48*/
	vnt_calculate_ofdm_rate(vnt_get_ofdm_rate(priv, RATE_48M),
				bb_type, &tx_rate[6], &rsv_time[6]);

	/*RSPINF_a_54*/
	vnt_calculate_ofdm_rate(vnt_get_ofdm_rate(priv, RATE_54M),
				bb_type, &tx_rate[7], &rsv_time[7]);

	/*RSPINF_a_72*/
	vnt_calculate_ofdm_rate(vnt_get_ofdm_rate(priv, RATE_54M),
				bb_type, &tx_rate[8], &rsv_time[8]);

	put_unaligned(phy[0].len, (u16 *)&data[0]);
	data[2] = phy[0].signal;
	data[3] = phy[0].service;

	put_unaligned(phy[1].len, (u16 *)&data[4]);
	data[6] = phy[1].signal;
	data[7] = phy[1].service;

	put_unaligned(phy[2].len, (u16 *)&data[8]);
	data[10] = phy[2].signal;
	data[11] = phy[2].service;

	put_unaligned(phy[3].len, (u16 *)&data[12]);
	data[14] = phy[3].signal;
	data[15] = phy[3].service;

	for (i = 0; i < 9; i++) {
		data[16 + i * 2] = tx_rate[i];
		data[16 + i * 2 + 1] = rsv_time[i];
	}

	vnt_control_out(priv, MESSAGE_TYPE_WRITE, MAC_REG_RSPINF_B_1,
			MESSAGE_REQUEST_MACREG, 34, &data[0]);
}
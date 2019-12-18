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
typedef  int u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct vnt_private {int sifs; scalar_t__ top_ofdm_basic_rate; int /*<<< orphan*/  preamble_type; scalar_t__ top_cck_basic_rate; } ;

/* Variables and functions */
 scalar_t__ PK_TYPE_11B ; 
 int vnt_get_frame_time (int /*<<< orphan*/ ,scalar_t__,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static u32 vnt_get_rsvtime(struct vnt_private *priv, u8 pkt_type,
			   u32 frame_length, u16 rate, int need_ack)
{
	u32 data_time, ack_time;

	data_time = vnt_get_frame_time(priv->preamble_type, pkt_type,
				       frame_length, rate);

	if (pkt_type == PK_TYPE_11B)
		ack_time = vnt_get_frame_time(priv->preamble_type, pkt_type,
					      14, (u16)priv->top_cck_basic_rate);
	else
		ack_time = vnt_get_frame_time(priv->preamble_type, pkt_type,
					      14, (u16)priv->top_ofdm_basic_rate);

	if (need_ack)
		return data_time + priv->sifs + ack_time;

	return data_time;
}
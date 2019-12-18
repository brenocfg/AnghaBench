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
typedef  scalar_t__ u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct vnt_private {scalar_t__ sifs; int /*<<< orphan*/  top_ofdm_basic_rate; int /*<<< orphan*/  preamble_type; int /*<<< orphan*/  top_cck_basic_rate; } ;
typedef  int /*<<< orphan*/  __le16 ;

/* Variables and functions */
 scalar_t__ PK_TYPE_11B ; 
 int /*<<< orphan*/  cpu_to_le16 (int /*<<< orphan*/ ) ; 
 scalar_t__ vnt_get_frame_time (int /*<<< orphan*/ ,scalar_t__,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static __le16 vnt_get_duration_le(struct vnt_private *priv, u8 pkt_type,
				  int need_ack)
{
	u32 ack_time = 0;

	if (need_ack) {
		if (pkt_type == PK_TYPE_11B)
			ack_time = vnt_get_frame_time(priv->preamble_type,
						      pkt_type, 14,
						      priv->top_cck_basic_rate);
		else
			ack_time = vnt_get_frame_time(priv->preamble_type,
						      pkt_type, 14,
						      priv->top_ofdm_basic_rate);

		return cpu_to_le16((u16)(priv->sifs + ack_time));
	}

	return 0;
}
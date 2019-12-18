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
typedef  int /*<<< orphan*/  u32 ;
typedef  scalar_t__ u16 ;
struct sk_buff {int /*<<< orphan*/  data; } ;
struct mlxsw_core {TYPE_1__* driver; } ;
struct TYPE_2__ {scalar_t__ txhdr_len; } ;

/* Variables and functions */
 int MLXSW_EMAD_END_TLV_LEN ; 
 scalar_t__ MLXSW_EMAD_ETH_HDR_LEN ; 
 scalar_t__ MLXSW_EMAD_MAX_FRAME_LEN ; 
 int MLXSW_EMAD_OP_TLV_LEN ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 struct sk_buff* netdev_alloc_skb (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  skb_reserve (struct sk_buff*,scalar_t__) ; 

__attribute__((used)) static struct sk_buff *mlxsw_emad_alloc(const struct mlxsw_core *mlxsw_core,
					u16 reg_len)
{
	struct sk_buff *skb;
	u16 emad_len;

	emad_len = (reg_len + sizeof(u32) + MLXSW_EMAD_ETH_HDR_LEN +
		    (MLXSW_EMAD_OP_TLV_LEN + MLXSW_EMAD_END_TLV_LEN) *
		    sizeof(u32) + mlxsw_core->driver->txhdr_len);
	if (emad_len > MLXSW_EMAD_MAX_FRAME_LEN)
		return NULL;

	skb = netdev_alloc_skb(NULL, emad_len);
	if (!skb)
		return NULL;
	memset(skb->data, 0, emad_len);
	skb_reserve(skb, emad_len);

	return skb;
}
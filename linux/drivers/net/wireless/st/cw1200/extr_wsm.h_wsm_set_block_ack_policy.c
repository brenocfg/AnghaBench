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
typedef  int /*<<< orphan*/  val ;
typedef  int /*<<< orphan*/  u8 ;
struct wsm_mib_block_ack_policy {int /*<<< orphan*/  rx_tid; int /*<<< orphan*/  tx_tid; } ;
struct cw1200_common {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  WSM_MIB_ID_BLOCK_ACK_POLICY ; 
 int wsm_write_mib (struct cw1200_common*,int /*<<< orphan*/ ,struct wsm_mib_block_ack_policy*,int) ; 

__attribute__((used)) static inline int wsm_set_block_ack_policy(struct cw1200_common *priv,
					   u8 tx_tid_policy,
					   u8 rx_tid_policy)
{
	struct wsm_mib_block_ack_policy val = {
		.tx_tid = tx_tid_policy,
		.rx_tid = rx_tid_policy,
	};
	return wsm_write_mib(priv, WSM_MIB_ID_BLOCK_ACK_POLICY, &val,
			     sizeof(val));
}
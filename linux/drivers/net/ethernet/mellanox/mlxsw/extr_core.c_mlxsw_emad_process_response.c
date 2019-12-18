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
struct sk_buff {int dummy; } ;
struct mlxsw_reg_trans {int /*<<< orphan*/  cb_priv; TYPE_1__* reg; int /*<<< orphan*/  (* cb ) (struct mlxsw_core*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  emad_status; int /*<<< orphan*/  active; } ;
struct mlxsw_core {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  len; } ;

/* Variables and functions */
 int EAGAIN ; 
 int /*<<< orphan*/  atomic_dec_and_test (int /*<<< orphan*/ *) ; 
 char* mlxsw_emad_op_tlv (struct sk_buff*) ; 
 int mlxsw_emad_process_status_skb (struct sk_buff*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mlxsw_emad_reg_payload (char*) ; 
 int /*<<< orphan*/  mlxsw_emad_trans_finish (struct mlxsw_reg_trans*,int) ; 
 int /*<<< orphan*/  mlxsw_emad_transmit_retry (struct mlxsw_core*,struct mlxsw_reg_trans*) ; 
 int /*<<< orphan*/  stub1 (struct mlxsw_core*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mlxsw_emad_process_response(struct mlxsw_core *mlxsw_core,
					struct mlxsw_reg_trans *trans,
					struct sk_buff *skb)
{
	int err;

	if (!atomic_dec_and_test(&trans->active))
		return;

	err = mlxsw_emad_process_status_skb(skb, &trans->emad_status);
	if (err == -EAGAIN) {
		mlxsw_emad_transmit_retry(mlxsw_core, trans);
	} else {
		if (err == 0) {
			char *op_tlv = mlxsw_emad_op_tlv(skb);

			if (trans->cb)
				trans->cb(mlxsw_core,
					  mlxsw_emad_reg_payload(op_tlv),
					  trans->reg->len, trans->cb_priv);
		}
		mlxsw_emad_trans_finish(trans, err);
	}
}
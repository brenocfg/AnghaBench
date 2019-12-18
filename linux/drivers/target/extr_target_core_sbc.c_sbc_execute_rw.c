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
struct se_cmd {int /*<<< orphan*/  data_direction; int /*<<< orphan*/  t_data_nents; int /*<<< orphan*/  t_data_sg; struct sbc_ops* protocol_data; } ;
struct sbc_ops {int /*<<< orphan*/  (* execute_rw ) (struct se_cmd*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
typedef  int /*<<< orphan*/  sense_reason_t ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct se_cmd*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static sense_reason_t
sbc_execute_rw(struct se_cmd *cmd)
{
	struct sbc_ops *ops = cmd->protocol_data;

	return ops->execute_rw(cmd, cmd->t_data_sg, cmd->t_data_nents,
			       cmd->data_direction);
}
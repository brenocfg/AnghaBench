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
struct tcmu_cmd {struct se_cmd* se_cmd; } ;
struct se_cmd {int se_cmd_flags; TYPE_1__* t_bidi_data_sg; scalar_t__ t_bidi_data_nents; int /*<<< orphan*/  data_length; } ;
struct TYPE_2__ {int /*<<< orphan*/  length; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  DATA_BLOCK_SIZE ; 
 int SCF_BIDI ; 
 size_t round_up (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline size_t tcmu_cmd_get_data_length(struct tcmu_cmd *tcmu_cmd)
{
	struct se_cmd *se_cmd = tcmu_cmd->se_cmd;
	size_t data_length = round_up(se_cmd->data_length, DATA_BLOCK_SIZE);

	if (se_cmd->se_cmd_flags & SCF_BIDI) {
		BUG_ON(!(se_cmd->t_bidi_data_sg && se_cmd->t_bidi_data_nents));
		data_length += round_up(se_cmd->t_bidi_data_sg->length,
				DATA_BLOCK_SIZE);
	}

	return data_length;
}
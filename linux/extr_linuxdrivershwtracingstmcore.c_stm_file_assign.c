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
struct stm_file {int /*<<< orphan*/  policy_node; int /*<<< orphan*/  output; struct stm_device* stm; } ;
struct stm_device {int dummy; } ;

/* Variables and functions */
 int stm_output_assign (struct stm_device*,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stp_policy_node_lookup (struct stm_device*,char*) ; 
 int /*<<< orphan*/  stp_policy_node_put (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int stm_file_assign(struct stm_file *stmf, char *id, unsigned int width)
{
	struct stm_device *stm = stmf->stm;
	int ret;

	stmf->policy_node = stp_policy_node_lookup(stm, id);

	ret = stm_output_assign(stm, width, stmf->policy_node, &stmf->output);

	if (stmf->policy_node)
		stp_policy_node_put(stmf->policy_node);

	return ret;
}
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
struct ocrdma_mqe {int dummy; } ;
struct ocrdma_mbx_query_config {int dummy; } ;
struct ocrdma_dev {int /*<<< orphan*/  attr; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  OCRDMA_CMD_QUERY_CONFIG ; 
 int /*<<< orphan*/  kfree (struct ocrdma_mqe*) ; 
 int /*<<< orphan*/  ocrdma_get_attr (struct ocrdma_dev*,int /*<<< orphan*/ *,struct ocrdma_mbx_query_config*) ; 
 struct ocrdma_mqe* ocrdma_init_emb_mqe (int /*<<< orphan*/ ,int) ; 
 int ocrdma_mbx_cmd (struct ocrdma_dev*,struct ocrdma_mqe*) ; 

__attribute__((used)) static int ocrdma_mbx_query_dev(struct ocrdma_dev *dev)
{
	int status = -ENOMEM;
	struct ocrdma_mbx_query_config *rsp;
	struct ocrdma_mqe *cmd;

	cmd = ocrdma_init_emb_mqe(OCRDMA_CMD_QUERY_CONFIG, sizeof(*cmd));
	if (!cmd)
		return status;
	status = ocrdma_mbx_cmd(dev, (struct ocrdma_mqe *)cmd);
	if (status)
		goto mbx_err;
	rsp = (struct ocrdma_mbx_query_config *)cmd;
	ocrdma_get_attr(dev, &dev->attr, rsp);
mbx_err:
	kfree(cmd);
	return status;
}
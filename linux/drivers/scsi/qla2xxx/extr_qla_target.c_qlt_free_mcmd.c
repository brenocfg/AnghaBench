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
struct qla_tgt_mgmt_cmd {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  mempool_free (struct qla_tgt_mgmt_cmd*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qla_tgt_mgmt_cmd_mempool ; 

void qlt_free_mcmd(struct qla_tgt_mgmt_cmd *mcmd)
{
	mempool_free(mcmd, qla_tgt_mgmt_cmd_mempool);
}
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
struct nvmet_tcp_cmd {int /*<<< orphan*/  cmd_pdu; int /*<<< orphan*/  rsp_pdu; int /*<<< orphan*/  data_pdu; int /*<<< orphan*/  r2t_pdu; } ;

/* Variables and functions */
 int /*<<< orphan*/  page_frag_free (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void nvmet_tcp_free_cmd(struct nvmet_tcp_cmd *c)
{
	page_frag_free(c->r2t_pdu);
	page_frag_free(c->data_pdu);
	page_frag_free(c->rsp_pdu);
	page_frag_free(c->cmd_pdu);
}
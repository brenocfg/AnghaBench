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
typedef  int /*<<< orphan*/  uint8_t ;
struct iscsi_task {int hdr_max; struct iscsi_hdr* hdr; struct iscsi_iser_task* dd_data; } ;
struct TYPE_2__ {int /*<<< orphan*/  iscsi_header; } ;
struct iscsi_iser_task {TYPE_1__ desc; } ;
struct iscsi_hdr {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static int
iscsi_iser_pdu_alloc(struct iscsi_task *task, uint8_t opcode)
{
	struct iscsi_iser_task *iser_task = task->dd_data;

	task->hdr = (struct iscsi_hdr *)&iser_task->desc.iscsi_header;
	task->hdr_max = sizeof(iser_task->desc.iscsi_header);

	return 0;
}
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
typedef  scalar_t__ u16 ;
struct scsi_cmnd {int /*<<< orphan*/  request; } ;
struct pqi_ctrl_info {scalar_t__ max_hw_queue_index; } ;

/* Variables and functions */
 int /*<<< orphan*/  blk_mq_unique_tag (int /*<<< orphan*/ ) ; 
 scalar_t__ blk_mq_unique_tag_to_hwq (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline u16 pqi_get_hw_queue(struct pqi_ctrl_info *ctrl_info,
	struct scsi_cmnd *scmd)
{
	u16 hw_queue;

	hw_queue = blk_mq_unique_tag_to_hwq(blk_mq_unique_tag(scmd->request));
	if (hw_queue > ctrl_info->max_hw_queue_index)
		hw_queue = 0;

	return hw_queue;
}
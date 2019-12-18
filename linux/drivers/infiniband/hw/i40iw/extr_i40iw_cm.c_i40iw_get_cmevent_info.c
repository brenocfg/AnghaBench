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
typedef  scalar_t__ u8 ;
struct iw_cm_id {int /*<<< orphan*/  m_remote_addr; int /*<<< orphan*/  m_local_addr; } ;
struct iw_cm_event {int /*<<< orphan*/  ord; int /*<<< orphan*/  ird; scalar_t__ private_data_len; void* private_data; int /*<<< orphan*/  remote_addr; int /*<<< orphan*/  local_addr; } ;
struct TYPE_2__ {scalar_t__ size; } ;
struct i40iw_cm_node {int /*<<< orphan*/  ord_size; int /*<<< orphan*/  ird_size; TYPE_1__ pdata; scalar_t__ pdata_buf; } ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static inline void i40iw_get_cmevent_info(struct i40iw_cm_node *cm_node,
					  struct iw_cm_id *cm_id,
					  struct iw_cm_event *event)
{
	memcpy(&event->local_addr, &cm_id->m_local_addr,
	       sizeof(event->local_addr));
	memcpy(&event->remote_addr, &cm_id->m_remote_addr,
	       sizeof(event->remote_addr));
	if (cm_node) {
		event->private_data = (void *)cm_node->pdata_buf;
		event->private_data_len = (u8)cm_node->pdata.size;
		event->ird = cm_node->ird_size;
		event->ord = cm_node->ord_size;
	}
}
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
typedef  enum dm_queue_mode { ____Placeholder_dm_queue_mode } dm_queue_mode ;

/* Variables and functions */
 int DM_TYPE_MQ_REQUEST_BASED ; 
 int DM_TYPE_REQUEST_BASED ; 

__attribute__((used)) static bool __table_type_request_based(enum dm_queue_mode table_type)
{
	return (table_type == DM_TYPE_REQUEST_BASED ||
		table_type == DM_TYPE_MQ_REQUEST_BASED);
}
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
struct pqi_ctrl_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BMIC_WRITE_HOST_WELLNESS ; 
 int pqi_send_ctrl_raid_request (struct pqi_ctrl_info*,int /*<<< orphan*/ ,void*,size_t) ; 

__attribute__((used)) static inline int pqi_write_host_wellness(struct pqi_ctrl_info *ctrl_info,
	void *buffer, size_t buffer_length)
{
	return pqi_send_ctrl_raid_request(ctrl_info, BMIC_WRITE_HOST_WELLNESS,
					buffer, buffer_length);
}
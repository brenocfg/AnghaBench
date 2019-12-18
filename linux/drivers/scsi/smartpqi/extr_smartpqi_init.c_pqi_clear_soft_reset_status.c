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
typedef  int /*<<< orphan*/  u8 ;
struct pqi_ctrl_info {int /*<<< orphan*/  soft_reset_status; } ;

/* Variables and functions */
 int /*<<< orphan*/  pqi_read_soft_reset_status (struct pqi_ctrl_info*) ; 
 int /*<<< orphan*/  writeb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void pqi_clear_soft_reset_status(struct pqi_ctrl_info *ctrl_info,
						u8 clear)
{
	u8 status;

	if (!ctrl_info->soft_reset_status)
		return;

	status = pqi_read_soft_reset_status(ctrl_info);
	status &= ~clear;
	writeb(status, ctrl_info->soft_reset_status);
}
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
 int /*<<< orphan*/  readb (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline u8 pqi_read_soft_reset_status(struct pqi_ctrl_info *ctrl_info)
{
	if (!ctrl_info->soft_reset_status)
		return 0;

	return readb(ctrl_info->soft_reset_status);
}
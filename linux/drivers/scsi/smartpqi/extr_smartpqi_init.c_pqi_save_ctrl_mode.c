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
typedef  enum pqi_ctrl_mode { ____Placeholder_pqi_ctrl_mode } pqi_ctrl_mode ;

/* Variables and functions */
 int /*<<< orphan*/  sis_write_driver_scratch (struct pqi_ctrl_info*,int) ; 

__attribute__((used)) static inline void pqi_save_ctrl_mode(struct pqi_ctrl_info *ctrl_info,
	enum pqi_ctrl_mode mode)
{
	sis_write_driver_scratch(ctrl_info, mode);
}
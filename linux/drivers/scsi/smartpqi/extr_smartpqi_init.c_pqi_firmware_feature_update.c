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
struct pqi_firmware_feature {int /*<<< orphan*/  (* feature_status ) (struct pqi_ctrl_info*,struct pqi_firmware_feature*) ;} ;
struct pqi_ctrl_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct pqi_ctrl_info*,struct pqi_firmware_feature*) ; 

__attribute__((used)) static inline void pqi_firmware_feature_update(struct pqi_ctrl_info *ctrl_info,
	struct pqi_firmware_feature *firmware_feature)
{
	if (firmware_feature->feature_status)
		firmware_feature->feature_status(ctrl_info, firmware_feature);
}
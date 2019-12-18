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
struct pqi_raid_error_info {int dummy; } ;
struct pqi_ctrl_info {int dummy; } ;
struct bmic_csmi_smp_passthru_buffer {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BMIC_CSMI_PASSTHRU ; 
 int pqi_send_ctrl_raid_with_error (struct pqi_ctrl_info*,int /*<<< orphan*/ ,struct bmic_csmi_smp_passthru_buffer*,size_t,struct pqi_raid_error_info*) ; 

int pqi_csmi_smp_passthru(struct pqi_ctrl_info *ctrl_info,
	struct bmic_csmi_smp_passthru_buffer *buffer, size_t buffer_length,
	struct pqi_raid_error_info *error_info)
{
	return pqi_send_ctrl_raid_with_error(ctrl_info, BMIC_CSMI_PASSTHRU,
		buffer, buffer_length, error_info);
}
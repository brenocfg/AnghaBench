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
struct vp_config_entry_24xx {int /*<<< orphan*/  options_idx1; } ;
struct scsi_qla_host {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT_4 ; 
 int /*<<< orphan*/  BIT_5 ; 
 scalar_t__ qla_dual_mode_enabled (struct scsi_qla_host*) ; 
 scalar_t__ qla_tgt_mode_enabled (struct scsi_qla_host*) ; 

void
qlt_modify_vp_config(struct scsi_qla_host *vha,
	struct vp_config_entry_24xx *vpmod)
{
	/* enable target mode.  Bit5 = 1 => disable */
	if (qla_tgt_mode_enabled(vha) || qla_dual_mode_enabled(vha))
		vpmod->options_idx1 &= ~BIT_5;

	/* Disable ini mode, if requested.  bit4 = 1 => disable */
	if (qla_tgt_mode_enabled(vha))
		vpmod->options_idx1 &= ~BIT_4;
}
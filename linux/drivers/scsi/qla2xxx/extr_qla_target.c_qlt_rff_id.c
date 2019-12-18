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
typedef  int u8 ;
struct scsi_qla_host {int dummy; } ;

/* Variables and functions */
 int BIT_0 ; 
 int BIT_1 ; 
 scalar_t__ qla_dual_mode_enabled (struct scsi_qla_host*) ; 
 scalar_t__ qla_ini_mode_enabled (struct scsi_qla_host*) ; 
 scalar_t__ qla_tgt_mode_enabled (struct scsi_qla_host*) ; 

u8
qlt_rff_id(struct scsi_qla_host *vha)
{
	u8 fc4_feature = 0;
	/*
	 * FC-4 Feature bit 0 indicates target functionality to the name server.
	 */
	if (qla_tgt_mode_enabled(vha)) {
		fc4_feature = BIT_0;
	} else if (qla_ini_mode_enabled(vha)) {
		fc4_feature = BIT_1;
	} else if (qla_dual_mode_enabled(vha))
		fc4_feature = BIT_0 | BIT_1;

	return fc4_feature;
}
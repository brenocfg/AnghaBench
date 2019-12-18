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
typedef  size_t uint32_t ;
struct scsi_qla_host {int /*<<< orphan*/ * reg_tbl; TYPE_1__* isp_ops; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* wr_reg_direct ) (struct scsi_qla_host*,int /*<<< orphan*/ ,size_t const) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct scsi_qla_host*,int /*<<< orphan*/ ,size_t const) ; 

__attribute__((used)) static inline void qla4_8xxx_wr_direct(struct scsi_qla_host *ha,
				       const uint32_t crb_reg,
				       const uint32_t value)
{
	ha->isp_ops->wr_reg_direct(ha, ha->reg_tbl[crb_reg], value);
}
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
typedef  int /*<<< orphan*/  scsi_qla_host_t ;

/* Variables and functions */
 int /*<<< orphan*/  qla2x00_init_eft_trace (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  qla2x00_init_fce_trace (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
qla2x00_alloc_offload_mem(scsi_qla_host_t *vha)
{
	qla2x00_init_fce_trace(vha);
	qla2x00_init_eft_trace(vha);
}
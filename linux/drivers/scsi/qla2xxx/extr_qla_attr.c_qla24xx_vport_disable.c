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
struct fc_vport {int /*<<< orphan*/ * dd_data; } ;
typedef  int /*<<< orphan*/  scsi_qla_host_t ;

/* Variables and functions */
 int /*<<< orphan*/  qla24xx_disable_vp (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  qla24xx_enable_vp (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
qla24xx_vport_disable(struct fc_vport *fc_vport, bool disable)
{
	scsi_qla_host_t *vha = fc_vport->dd_data;

	if (disable)
		qla24xx_disable_vp(vha);
	else
		qla24xx_enable_vp(vha);

	return 0;
}
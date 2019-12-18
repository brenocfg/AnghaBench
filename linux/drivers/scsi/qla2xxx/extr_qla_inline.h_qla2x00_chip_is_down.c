#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {TYPE_2__* hw; } ;
typedef  TYPE_3__ scsi_qla_host_t ;
struct TYPE_6__ {int /*<<< orphan*/  fw_started; } ;
struct TYPE_7__ {TYPE_1__ flags; } ;

/* Variables and functions */
 scalar_t__ qla2x00_reset_active (TYPE_3__*) ; 

__attribute__((used)) static inline int
qla2x00_chip_is_down(scsi_qla_host_t *vha)
{
	return (qla2x00_reset_active(vha) || !vha->hw->flags.fw_started);
}
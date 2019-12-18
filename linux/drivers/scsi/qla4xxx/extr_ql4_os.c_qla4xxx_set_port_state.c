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
typedef  int /*<<< orphan*/  uint32_t ;
struct scsi_qla_host {int /*<<< orphan*/  flags; } ;
struct iscsi_cls_host {int /*<<< orphan*/  port_state; } ;
struct Scsi_Host {struct iscsi_cls_host* shost_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  AF_LINK_UP ; 
 int /*<<< orphan*/  ISCSI_PORT_STATE_DOWN ; 
 int /*<<< orphan*/  ISCSI_PORT_STATE_UP ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct scsi_qla_host* to_qla_host (struct Scsi_Host*) ; 

__attribute__((used)) static void qla4xxx_set_port_state(struct Scsi_Host *shost)
{
	struct scsi_qla_host *ha = to_qla_host(shost);
	struct iscsi_cls_host *ihost = shost->shost_data;
	uint32_t state = ISCSI_PORT_STATE_DOWN;

	if (test_bit(AF_LINK_UP, &ha->flags))
		state = ISCSI_PORT_STATE_UP;

	ihost->port_state = state;
}
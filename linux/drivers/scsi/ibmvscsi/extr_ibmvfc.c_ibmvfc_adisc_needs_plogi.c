#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_3__ {scalar_t__ port_name; scalar_t__ node_name; } ;
struct ibmvfc_target {scalar_t__ scsi_id; TYPE_1__ ids; } ;
struct TYPE_4__ {int /*<<< orphan*/ * response; } ;
struct ibmvfc_passthru_mad {TYPE_2__ fc_iu; } ;

/* Variables and functions */
 scalar_t__ be32_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ wwn_to_u64 (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ibmvfc_adisc_needs_plogi(struct ibmvfc_passthru_mad *mad,
				    struct ibmvfc_target *tgt)
{
	if (wwn_to_u64((u8 *)&mad->fc_iu.response[2]) != tgt->ids.port_name)
		return 1;
	if (wwn_to_u64((u8 *)&mad->fc_iu.response[4]) != tgt->ids.node_name)
		return 1;
	if (be32_to_cpu(mad->fc_iu.response[6]) != tgt->scsi_id)
		return 1;
	return 0;
}
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
struct ibmvfc_host {int num_targets; TYPE_1__* disc_buf; } ;
struct TYPE_2__ {int /*<<< orphan*/ * scsi_id; } ;

/* Variables and functions */
 int IBMVFC_DISC_TGT_SCSI_ID_MASK ; 
 int be32_to_cpu (int /*<<< orphan*/ ) ; 
 int ibmvfc_alloc_target (struct ibmvfc_host*,int) ; 

__attribute__((used)) static int ibmvfc_alloc_targets(struct ibmvfc_host *vhost)
{
	int i, rc;

	for (i = 0, rc = 0; !rc && i < vhost->num_targets; i++)
		rc = ibmvfc_alloc_target(vhost,
					 be32_to_cpu(vhost->disc_buf->scsi_id[i]) &
					 IBMVFC_DISC_TGT_SCSI_ID_MASK);

	return rc;
}
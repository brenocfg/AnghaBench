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
struct TYPE_2__ {scalar_t__ typ; } ;
struct snic_tgt {TYPE_1__ tdata; } ;
struct scsi_device {int dummy; } ;

/* Variables and functions */
 scalar_t__ SNIC_TGT_DAS ; 
 int /*<<< orphan*/  scsi_target (struct scsi_device*) ; 
 struct snic_tgt* starget_to_tgt (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
snic_dev_reset_supported(struct scsi_device *sdev)
{
	struct snic_tgt *tgt = starget_to_tgt(scsi_target(sdev));

	if (tgt->tdata.typ == SNIC_TGT_DAS)
		return 0;

	return 1;
}
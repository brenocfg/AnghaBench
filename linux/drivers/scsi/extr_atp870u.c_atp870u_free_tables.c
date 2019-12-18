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
struct atp_unit {TYPE_2__** id; TYPE_1__* pdev; } ;
struct Scsi_Host {int /*<<< orphan*/  hostdata; } ;
struct TYPE_4__ {int /*<<< orphan*/ * prd_table; int /*<<< orphan*/  prd_bus; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void atp870u_free_tables(struct Scsi_Host *host)
{
	struct atp_unit *atp_dev = (struct atp_unit *)&host->hostdata;
	int j, k;
	for (j=0; j < 2; j++) {
		for (k = 0; k < 16; k++) {
			if (!atp_dev->id[j][k].prd_table)
				continue;
			dma_free_coherent(&atp_dev->pdev->dev, 1024, atp_dev->id[j][k].prd_table, atp_dev->id[j][k].prd_bus);
			atp_dev->id[j][k].prd_table = NULL;
		}
	}
}
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
struct scb {int sg_count; scalar_t__ sg_list_busaddr; TYPE_2__* sg_map; } ;
struct TYPE_3__ {int /*<<< orphan*/  sg_dmat; } ;
struct ahd_softc {TYPE_1__ scb_data; } ;
struct TYPE_4__ {int /*<<< orphan*/  dmamap; } ;

/* Variables and functions */
 int /*<<< orphan*/  ahd_dmamap_sync (struct ahd_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int,int) ; 
 int ahd_sg_size (struct ahd_softc*) ; 

void
ahd_sync_sglist(struct ahd_softc *ahd, struct scb *scb, int op)
{
	if (scb->sg_count == 0)
		return;

	ahd_dmamap_sync(ahd, ahd->scb_data.sg_dmat,
			scb->sg_map->dmamap,
			/*offset*/scb->sg_list_busaddr - ahd_sg_size(ahd),
			/*len*/ahd_sg_size(ahd) * scb->sg_count, op);
}
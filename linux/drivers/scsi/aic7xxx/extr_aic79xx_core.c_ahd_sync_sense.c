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
struct scb {int /*<<< orphan*/  sense_busaddr; TYPE_2__* sense_map; } ;
struct TYPE_3__ {int /*<<< orphan*/  sense_dmat; } ;
struct ahd_softc {TYPE_1__ scb_data; } ;
struct TYPE_4__ {int /*<<< orphan*/  dmamap; } ;

/* Variables and functions */
 int /*<<< orphan*/  AHD_SENSE_BUFSIZE ; 
 int /*<<< orphan*/  ahd_dmamap_sync (struct ahd_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
ahd_sync_sense(struct ahd_softc *ahd, struct scb *scb, int op)
{
	ahd_dmamap_sync(ahd, ahd->scb_data.sense_dmat,
			scb->sense_map->dmamap,
			/*offset*/scb->sense_busaddr,
			/*len*/AHD_SENSE_BUFSIZE, op);
}
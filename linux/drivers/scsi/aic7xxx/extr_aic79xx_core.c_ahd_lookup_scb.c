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
typedef  size_t u_int ;
struct scb {int dummy; } ;
struct TYPE_2__ {struct scb** scbindex; } ;
struct ahd_softc {TYPE_1__ scb_data; } ;

/* Variables and functions */
 size_t AHD_SCB_MAX ; 
 int BUS_DMASYNC_POSTREAD ; 
 int BUS_DMASYNC_POSTWRITE ; 
 int /*<<< orphan*/  ahd_sync_scb (struct ahd_softc*,struct scb*,int) ; 

struct scb *
ahd_lookup_scb(struct ahd_softc *ahd, u_int tag)
{
	struct scb* scb;

	if (tag >= AHD_SCB_MAX)
		return (NULL);
	scb = ahd->scb_data.scbindex[tag];
	if (scb != NULL)
		ahd_sync_scb(ahd, scb,
			     BUS_DMASYNC_POSTREAD|BUS_DMASYNC_POSTWRITE);
	return (scb);
}
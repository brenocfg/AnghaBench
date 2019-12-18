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
struct scsi_sense_data {int dummy; } ;
struct scb {int dummy; } ;
struct ahc_softc {TYPE_1__* scb_data; } ;
struct TYPE_2__ {struct scsi_sense_data* sense; struct scb* scbarray; } ;

/* Variables and functions */

struct scsi_sense_data *
ahc_get_sense_buf(struct ahc_softc *ahc, struct scb *scb)
{
	int offset;

	offset = scb - ahc->scb_data->scbarray;
	return (&ahc->scb_data->sense[offset]);
}
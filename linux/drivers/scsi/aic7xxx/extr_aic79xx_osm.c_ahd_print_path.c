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
struct scb {int dummy; } ;
struct ahd_softc {TYPE_2__* platform_data; } ;
struct TYPE_4__ {TYPE_1__* host; } ;
struct TYPE_3__ {int /*<<< orphan*/  host_no; } ;

/* Variables and functions */
 char SCB_GET_CHANNEL (struct ahd_softc*,struct scb*) ; 
 int SCB_GET_LUN (struct scb*) ; 
 int SCB_GET_TARGET (struct ahd_softc*,struct scb*) ; 
 int /*<<< orphan*/  printk (char*,int /*<<< orphan*/ ,char,int,int) ; 

void
ahd_print_path(struct ahd_softc *ahd, struct scb *scb)
{
	printk("(scsi%d:%c:%d:%d): ",
	       ahd->platform_data->host->host_no,
	       scb != NULL ? SCB_GET_CHANNEL(ahd, scb) : 'X',
	       scb != NULL ? SCB_GET_TARGET(ahd, scb) : -1,
	       scb != NULL ? SCB_GET_LUN(scb) : -1);
}
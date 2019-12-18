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
struct scb {int dummy; } ;
struct ahc_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAM_REQUEUE_REQ ; 
 int /*<<< orphan*/  ROLE_UNKNOWN ; 
 char SCB_GET_CHANNEL (struct ahc_softc*,struct scb*) ; 
 int SCB_GET_LUN (struct scb*) ; 
 int SCB_GET_TARGET (struct ahc_softc*,struct scb*) ; 
 int /*<<< orphan*/  SCB_LIST_NULL ; 
 int /*<<< orphan*/  SEARCH_COMPLETE ; 
 int /*<<< orphan*/  ahc_platform_freeze_devq (struct ahc_softc*,struct scb*) ; 
 int /*<<< orphan*/  ahc_search_qinfifo (struct ahc_softc*,int,char,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
ahc_freeze_devq(struct ahc_softc *ahc, struct scb *scb)
{
	int	target;
	char	channel;
	int	lun;

	target = SCB_GET_TARGET(ahc, scb);
	lun = SCB_GET_LUN(scb);
	channel = SCB_GET_CHANNEL(ahc, scb);
	
	ahc_search_qinfifo(ahc, target, channel, lun,
			   /*tag*/SCB_LIST_NULL, ROLE_UNKNOWN,
			   CAM_REQUEUE_REQ, SEARCH_COMPLETE);

	ahc_platform_freeze_devq(ahc, scb);
}
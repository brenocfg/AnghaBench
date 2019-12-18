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
 int /*<<< orphan*/  SCB_GET_CHANNEL (struct ahc_softc*,struct scb*) ; 
 int /*<<< orphan*/  SCB_GET_LUN (struct scb*) ; 
 int /*<<< orphan*/  SCB_GET_TARGET (struct ahc_softc*,struct scb*) ; 
 int /*<<< orphan*/  SCB_LIST_NULL ; 
 int /*<<< orphan*/  ahc_platform_abort_scbs (struct ahc_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
ahc_platform_freeze_devq(struct ahc_softc *ahc, struct scb *scb)
{
	ahc_platform_abort_scbs(ahc, SCB_GET_TARGET(ahc, scb),
				SCB_GET_CHANNEL(ahc, scb),
				SCB_GET_LUN(scb), SCB_LIST_NULL,
				ROLE_UNKNOWN, CAM_REQUEUE_REQ);
}
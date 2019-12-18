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
typedef  int uint32_t ;
struct scb {TYPE_1__* hscb; } ;
struct ahc_softc {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  sgptr; } ;

/* Variables and functions */
 int SG_RESID_VALID ; 
 int /*<<< orphan*/  ahc_calc_residual (struct ahc_softc*,struct scb*) ; 
 int ahc_le32toh (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
ahc_update_residual(struct ahc_softc *ahc, struct scb *scb)
{
	uint32_t sgptr;

	sgptr = ahc_le32toh(scb->hscb->sgptr);
	if ((sgptr & SG_RESID_VALID) != 0)
		ahc_calc_residual(ahc, scb);
}
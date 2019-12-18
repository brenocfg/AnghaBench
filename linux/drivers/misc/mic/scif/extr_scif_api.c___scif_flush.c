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
struct scif_endpt {int state; int /*<<< orphan*/  conwq; } ;
typedef  scalar_t__ scif_epd_t ;

/* Variables and functions */
 int SCIFEP_CLLISTEN ; 
#define  SCIFEP_LISTENING 128 
 int /*<<< orphan*/  wake_up_interruptible (int /*<<< orphan*/ *) ; 

int __scif_flush(scif_epd_t epd)
{
	struct scif_endpt *ep = (struct scif_endpt *)epd;

	switch (ep->state) {
	case SCIFEP_LISTENING:
	{
		ep->state = SCIFEP_CLLISTEN;

		/* If an accept is waiting wake it up */
		wake_up_interruptible(&ep->conwq);
		break;
	}
	default:
		break;
	}
	return 0;
}
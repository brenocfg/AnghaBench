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
struct genwqe_dev {scalar_t__ card_state; } ;
struct ddcb_requ {int dummy; } ;

/* Variables and functions */
 scalar_t__ GENWQE_CARD_USED ; 
 scalar_t__ GENWQE_REQU_FINISHED ; 
 scalar_t__ ddcb_requ_get_state (struct ddcb_requ*) ; 

__attribute__((used)) static int ddcb_requ_finished(struct genwqe_dev *cd, struct ddcb_requ *req)
{
	return (ddcb_requ_get_state(req) == GENWQE_REQU_FINISHED) ||
		(cd->card_state != GENWQE_CARD_USED);
}
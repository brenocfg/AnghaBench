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
struct orc_scb {int /*<<< orphan*/  scbidx; int /*<<< orphan*/  status; } ;
struct orc_host {scalar_t__ base; } ;

/* Variables and functions */
 int /*<<< orphan*/  ORCSCB_POST ; 
 scalar_t__ ORC_PQUEUE ; 
 int /*<<< orphan*/  outb (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void orc_exec_scb(struct orc_host * host, struct orc_scb * scb)
{
	scb->status = ORCSCB_POST;
	outb(scb->scbidx, host->base + ORC_PQUEUE);
}
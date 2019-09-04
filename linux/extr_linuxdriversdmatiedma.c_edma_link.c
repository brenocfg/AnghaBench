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
struct edma_cc {unsigned int num_slots; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 unsigned int EDMA_CHAN_SLOT (unsigned int) ; 
 scalar_t__ EDMA_CTLR (unsigned int) ; 
 int /*<<< orphan*/  PARM_LINK_BCNTRLD ; 
 int /*<<< orphan*/  PARM_OFFSET (unsigned int) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  edma_param_modify (struct edma_cc*,int /*<<< orphan*/ ,unsigned int,int,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void edma_link(struct edma_cc *ecc, unsigned from, unsigned to)
{
	if (unlikely(EDMA_CTLR(from) != EDMA_CTLR(to)))
		dev_warn(ecc->dev, "Ignoring eDMA instance for linking\n");

	from = EDMA_CHAN_SLOT(from);
	to = EDMA_CHAN_SLOT(to);
	if (from >= ecc->num_slots || to >= ecc->num_slots)
		return;

	edma_param_modify(ecc, PARM_LINK_BCNTRLD, from, 0xffff0000,
			  PARM_OFFSET(to));
}
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
struct TYPE_3__ {scalar_t__ base; } ;
struct TYPE_4__ {TYPE_1__ njet; } ;
struct IsdnCardState {TYPE_2__ hw; } ;

/* Variables and functions */
 scalar_t__ NETJET_IRQMASK0 ; 
 scalar_t__ NETJET_IRQMASK1 ; 
 int /*<<< orphan*/  byteout (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  release_region (scalar_t__,int) ; 
 int /*<<< orphan*/  releasetiger (struct IsdnCardState*) ; 

void
release_io_netjet(struct IsdnCardState *cs)
{
	byteout(cs->hw.njet.base + NETJET_IRQMASK0, 0);
	byteout(cs->hw.njet.base + NETJET_IRQMASK1, 0);
	releasetiger(cs);
	release_region(cs->hw.njet.base, 256);
}
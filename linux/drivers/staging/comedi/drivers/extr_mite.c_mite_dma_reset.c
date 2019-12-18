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
struct mite_channel {int /*<<< orphan*/  channel; TYPE_1__* mite; } ;
struct TYPE_2__ {scalar_t__ mmio; } ;

/* Variables and functions */
 int CHOR_DMARESET ; 
 int CHOR_FRESET ; 
 scalar_t__ MITE_CHOR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static void mite_dma_reset(struct mite_channel *mite_chan)
{
	writel(CHOR_DMARESET | CHOR_FRESET,
	       mite_chan->mite->mmio + MITE_CHOR(mite_chan->channel));
}
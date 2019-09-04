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
struct rcar_drif {int /*<<< orphan*/  dmach; } ;

/* Variables and functions */
 int /*<<< orphan*/  RCAR_DRIF_SIIER ; 
 int /*<<< orphan*/  dmaengine_terminate_sync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcar_drif_write (struct rcar_drif*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void rcar_drif_stop_channel(struct rcar_drif *ch)
{
	/* Disable DMA receive interrupt */
	rcar_drif_write(ch, RCAR_DRIF_SIIER, 0x00000000);

	/* Terminate all DMA transfers */
	dmaengine_terminate_sync(ch->dmach);
}
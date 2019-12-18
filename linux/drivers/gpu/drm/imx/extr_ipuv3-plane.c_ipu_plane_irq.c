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
struct ipu_plane {int /*<<< orphan*/  ipu_ch; int /*<<< orphan*/  ipu; } ;

/* Variables and functions */
 int /*<<< orphan*/  IPU_IRQ_EOF ; 
 int ipu_idmac_channel_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int ipu_plane_irq(struct ipu_plane *ipu_plane)
{
	return ipu_idmac_channel_irq(ipu_plane->ipu, ipu_plane->ipu_ch,
				     IPU_IRQ_EOF);
}
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
struct mxs_auart_port {int flags; } ;

/* Variables and functions */
 int MXS_AUART_DMA_ENABLED ; 

__attribute__((used)) static inline bool auart_dma_enabled(struct mxs_auart_port *s)
{
	return s->flags & MXS_AUART_DMA_ENABLED;
}
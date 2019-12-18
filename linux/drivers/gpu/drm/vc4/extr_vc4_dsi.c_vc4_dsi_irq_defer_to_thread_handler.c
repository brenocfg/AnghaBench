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
typedef  int /*<<< orphan*/  u32 ;
struct vc4_dsi {int dummy; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  DSI_PORT_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INT_STAT ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int /*<<< orphan*/  IRQ_WAKE_THREAD ; 

__attribute__((used)) static irqreturn_t vc4_dsi_irq_defer_to_thread_handler(int irq, void *data)
{
	struct vc4_dsi *dsi = data;
	u32 stat = DSI_PORT_READ(INT_STAT);

	if (!stat)
		return IRQ_NONE;

	return IRQ_WAKE_THREAD;
}
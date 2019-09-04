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
struct dispc_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DISPC_IRQ_FRAMEDONEWB ; 

__attribute__((used)) static u32 dispc_wb_get_framedone_irq(struct dispc_device *dispc)
{
	return DISPC_IRQ_FRAMEDONEWB;
}
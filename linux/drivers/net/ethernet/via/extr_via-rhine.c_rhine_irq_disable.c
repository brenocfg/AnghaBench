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
struct rhine_private {scalar_t__ base; } ;

/* Variables and functions */
 scalar_t__ IntrEnable ; 
 int /*<<< orphan*/  iowrite16 (int,scalar_t__) ; 

__attribute__((used)) static void rhine_irq_disable(struct rhine_private *rp)
{
	iowrite16(0x0000, rp->base + IntrEnable);
}
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
struct vop_device {int dummy; } ;
struct mic_irq {int dummy; } ;

/* Variables and functions */
 void mic_free_card_irq (struct mic_irq*,void*) ; 

__attribute__((used)) static void __mic_free_irq(struct vop_device *vpdev,
			   struct mic_irq *cookie, void *data)
{
	return mic_free_card_irq(cookie, data);
}
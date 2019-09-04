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
struct irq_data {int irq; } ;
struct TYPE_2__ {int intena; } ;

/* Variables and functions */
 int IF_SETCLR ; 
 int IRQ_USER ; 
 TYPE_1__ amiga_custom ; 

__attribute__((used)) static void amiga_irq_enable(struct irq_data *data)
{
	amiga_custom.intena = IF_SETCLR | (1 << (data->irq - IRQ_USER));
}
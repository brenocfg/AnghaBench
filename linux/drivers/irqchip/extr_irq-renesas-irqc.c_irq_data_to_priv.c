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
struct irqc_priv {int dummy; } ;
struct irq_data {TYPE_1__* domain; } ;
struct TYPE_2__ {struct irqc_priv* host_data; } ;

/* Variables and functions */

__attribute__((used)) static struct irqc_priv *irq_data_to_priv(struct irq_data *data)
{
	return data->domain->host_data;
}
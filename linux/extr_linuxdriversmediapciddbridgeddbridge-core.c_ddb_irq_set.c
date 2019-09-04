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
typedef  size_t u32 ;
struct ddb_irq {void (* handler ) (void*) ;void* data; } ;
struct ddb {TYPE_1__* link; } ;
struct TYPE_2__ {struct ddb_irq* irq; } ;

/* Variables and functions */

struct ddb_irq *ddb_irq_set(struct ddb *dev, u32 link, u32 nr,
			    void (*handler)(void *), void *data)
{
	struct ddb_irq *irq = &dev->link[link].irq[nr];

	irq->handler = handler;
	irq->data = data;
	return irq;
}
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
struct sk_buff {int dummy; } ;
struct qtnf_bus {TYPE_1__* bus_ops; } ;
struct TYPE_2__ {int (* data_tx ) (struct qtnf_bus*,struct sk_buff*) ;} ;

/* Variables and functions */
 int stub1 (struct qtnf_bus*,struct sk_buff*) ; 

__attribute__((used)) static inline int qtnf_bus_data_tx(struct qtnf_bus *bus, struct sk_buff *skb)
{
	return bus->bus_ops->data_tx(bus, skb);
}
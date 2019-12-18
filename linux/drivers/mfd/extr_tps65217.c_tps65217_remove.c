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
struct tps65217 {int /*<<< orphan*/ * irq_domain; } ;
struct i2c_client {int dummy; } ;

/* Variables and functions */
 int TPS65217_NUM_IRQ ; 
 struct tps65217* i2c_get_clientdata (struct i2c_client*) ; 
 int /*<<< orphan*/  irq_dispose_mapping (unsigned int) ; 
 int /*<<< orphan*/  irq_domain_remove (int /*<<< orphan*/ *) ; 
 unsigned int irq_find_mapping (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int tps65217_remove(struct i2c_client *client)
{
	struct tps65217 *tps = i2c_get_clientdata(client);
	unsigned int virq;
	int i;

	for (i = 0; i < TPS65217_NUM_IRQ; i++) {
		virq = irq_find_mapping(tps->irq_domain, i);
		if (virq)
			irq_dispose_mapping(virq);
	}

	irq_domain_remove(tps->irq_domain);
	tps->irq_domain = NULL;

	return 0;
}
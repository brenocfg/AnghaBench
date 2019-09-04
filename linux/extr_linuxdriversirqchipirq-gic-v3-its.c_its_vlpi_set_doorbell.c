#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u32 ;
struct TYPE_4__ {TYPE_1__* vlpi_maps; } ;
struct its_device {TYPE_2__ event_map; } ;
struct irq_data {int dummy; } ;
struct TYPE_3__ {int db_enabled; } ;

/* Variables and functions */
 struct its_device* irq_data_get_irq_chip_data (struct irq_data*) ; 
 size_t its_get_event_id (struct irq_data*) ; 
 int /*<<< orphan*/  its_send_vmovi (struct its_device*,size_t) ; 

__attribute__((used)) static void its_vlpi_set_doorbell(struct irq_data *d, bool enable)
{
	struct its_device *its_dev = irq_data_get_irq_chip_data(d);
	u32 event = its_get_event_id(d);

	if (its_dev->event_map.vlpi_maps[event].db_enabled == enable)
		return;

	its_dev->event_map.vlpi_maps[event].db_enabled = enable;

	/*
	 * More fun with the architecture:
	 *
	 * Ideally, we'd issue a VMAPTI to set the doorbell to its LPI
	 * value or to 1023, depending on the enable bit. But that
	 * would be issueing a mapping for an /existing/ DevID+EventID
	 * pair, which is UNPREDICTABLE. Instead, let's issue a VMOVI
	 * to the /same/ vPE, using this opportunity to adjust the
	 * doorbell. Mouahahahaha. We loves it, Precious.
	 */
	its_send_vmovi(its_dev, event);
}
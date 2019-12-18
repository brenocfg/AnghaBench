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
struct serial_card_info {int num_ports; scalar_t__* ports; } ;
struct expansion_card {int dummy; } ;

/* Variables and functions */
 struct serial_card_info* ecard_get_drvdata (struct expansion_card*) ; 
 int /*<<< orphan*/  ecard_set_drvdata (struct expansion_card*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct serial_card_info*) ; 
 int /*<<< orphan*/  serial8250_unregister_port (scalar_t__) ; 

__attribute__((used)) static void serial_card_remove(struct expansion_card *ec)
{
	struct serial_card_info *info = ecard_get_drvdata(ec);
	int i;

	ecard_set_drvdata(ec, NULL);

	for (i = 0; i < info->num_ports; i++)
		if (info->ports[i] > 0)
			serial8250_unregister_port(info->ports[i]);

	kfree(info);
}
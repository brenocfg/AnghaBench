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
struct mc13xxx_adcdone_data {int /*<<< orphan*/  done; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  complete_all (int /*<<< orphan*/ *) ; 

__attribute__((used)) static irqreturn_t mc13xxx_handler_adcdone(int irq, void *data)
{
	struct mc13xxx_adcdone_data *adcdone_data = data;

	complete_all(&adcdone_data->done);

	return IRQ_HANDLED;
}
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
typedef  int /*<<< orphan*/  u32 ;
struct irq_handler_data {unsigned long sysino; } ;

/* Variables and functions */
 unsigned long sun4v_devino_to_sysino (int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static void sysino_handler_data(struct irq_handler_data *data,
				u32 devhandle, unsigned int devino)
{
	unsigned long sysino;

	sysino = sun4v_devino_to_sysino(devhandle, devino);
	data->sysino = sysino;
}
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
struct eeh_pe {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  eeh_pe_dev_traverse (struct eeh_pe*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  eeh_restore_one_device_bars ; 

void eeh_pe_restore_bars(struct eeh_pe *pe)
{
	/*
	 * We needn't take the EEH lock since eeh_pe_dev_traverse()
	 * will take that.
	 */
	eeh_pe_dev_traverse(pe, eeh_restore_one_device_bars, NULL);
}
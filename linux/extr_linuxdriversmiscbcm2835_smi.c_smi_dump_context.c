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
struct bcm2835_smi_instance {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  smi_dump_context_labelled (struct bcm2835_smi_instance*,char*) ; 

__attribute__((used)) static inline void smi_dump_context(struct bcm2835_smi_instance *inst)
{
	smi_dump_context_labelled(inst, "");
}
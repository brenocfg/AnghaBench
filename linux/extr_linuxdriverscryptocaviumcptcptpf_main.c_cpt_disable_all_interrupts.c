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
struct cpt_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  cpt_disable_ecc_interrupts (struct cpt_device*) ; 
 int /*<<< orphan*/  cpt_disable_exec_interrupts (struct cpt_device*) ; 
 int /*<<< orphan*/  cpt_disable_mbox_interrupts (struct cpt_device*) ; 

__attribute__((used)) static void cpt_disable_all_interrupts(struct cpt_device *cpt)
{
	cpt_disable_mbox_interrupts(cpt);
	cpt_disable_ecc_interrupts(cpt);
	cpt_disable_exec_interrupts(cpt);
}
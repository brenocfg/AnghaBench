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
struct dwc2_hsotg {int dummy; } ;

/* Variables and functions */
 unsigned int GHWCFG2_OP_MODE_HNP_SRP_CAPABLE ; 
 unsigned int GHWCFG2_OP_MODE_NO_HNP_SRP_CAPABLE ; 
 unsigned int GHWCFG2_OP_MODE_SRP_ONLY_CAPABLE ; 
 unsigned int dwc2_op_mode (struct dwc2_hsotg*) ; 

bool dwc2_hw_is_otg(struct dwc2_hsotg *hsotg)
{
	unsigned int op_mode = dwc2_op_mode(hsotg);

	return (op_mode == GHWCFG2_OP_MODE_HNP_SRP_CAPABLE) ||
		(op_mode == GHWCFG2_OP_MODE_SRP_ONLY_CAPABLE) ||
		(op_mode == GHWCFG2_OP_MODE_NO_HNP_SRP_CAPABLE);
}
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
typedef  int u8 ;
struct intel_dvo_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  TFP410_CTL_1 ; 
 int TFP410_CTL_1_PD ; 
 int /*<<< orphan*/  tfp410_readb (struct intel_dvo_device*,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static bool tfp410_get_hw_state(struct intel_dvo_device *dvo)
{
	u8 ctl1;

	if (!tfp410_readb(dvo, TFP410_CTL_1, &ctl1))
		return false;

	if (ctl1 & TFP410_CTL_1_PD)
		return true;
	else
		return false;
}
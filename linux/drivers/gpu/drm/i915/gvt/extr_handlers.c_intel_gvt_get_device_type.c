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
struct intel_gvt {int /*<<< orphan*/  dev_priv; } ;

/* Variables and functions */
 unsigned long D_BDW ; 
 unsigned long D_BXT ; 
 unsigned long D_CFL ; 
 unsigned long D_KBL ; 
 unsigned long D_SKL ; 
 scalar_t__ IS_BROADWELL (int /*<<< orphan*/ ) ; 
 scalar_t__ IS_BROXTON (int /*<<< orphan*/ ) ; 
 scalar_t__ IS_COFFEELAKE (int /*<<< orphan*/ ) ; 
 scalar_t__ IS_KABYLAKE (int /*<<< orphan*/ ) ; 
 scalar_t__ IS_SKYLAKE (int /*<<< orphan*/ ) ; 

unsigned long intel_gvt_get_device_type(struct intel_gvt *gvt)
{
	if (IS_BROADWELL(gvt->dev_priv))
		return D_BDW;
	else if (IS_SKYLAKE(gvt->dev_priv))
		return D_SKL;
	else if (IS_KABYLAKE(gvt->dev_priv))
		return D_KBL;
	else if (IS_BROXTON(gvt->dev_priv))
		return D_BXT;
	else if (IS_COFFEELAKE(gvt->dev_priv))
		return D_CFL;

	return 0;
}
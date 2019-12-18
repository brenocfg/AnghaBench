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
struct isp_ccdc_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __ccdc_enable (struct isp_ccdc_device*,int) ; 
 int /*<<< orphan*/  __ccdc_lsc_enable (struct isp_ccdc_device*,int) ; 
 scalar_t__ ccdc_lsc_is_configured (struct isp_ccdc_device*) ; 

__attribute__((used)) static void ccdc_enable(struct isp_ccdc_device *ccdc)
{
	if (ccdc_lsc_is_configured(ccdc))
		__ccdc_lsc_enable(ccdc, 1);
	__ccdc_enable(ccdc, 1);
}
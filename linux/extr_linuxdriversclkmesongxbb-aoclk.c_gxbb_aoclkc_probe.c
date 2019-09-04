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
struct platform_device {int dummy; } ;

/* Variables and functions */
 int gxbb_register_cec_ao_32k (struct platform_device*) ; 
 int meson_aoclkc_probe (struct platform_device*) ; 

__attribute__((used)) static int gxbb_aoclkc_probe(struct platform_device *pdev)
{
	int ret = gxbb_register_cec_ao_32k(pdev);
	if (ret)
		return ret;

	return meson_aoclkc_probe(pdev);
}
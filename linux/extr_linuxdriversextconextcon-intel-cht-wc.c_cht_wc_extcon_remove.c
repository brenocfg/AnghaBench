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
struct cht_wc_extcon_data {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  cht_wc_extcon_sw_control (struct cht_wc_extcon_data*,int) ; 
 struct cht_wc_extcon_data* platform_get_drvdata (struct platform_device*) ; 

__attribute__((used)) static int cht_wc_extcon_remove(struct platform_device *pdev)
{
	struct cht_wc_extcon_data *ext = platform_get_drvdata(pdev);

	cht_wc_extcon_sw_control(ext, false);

	return 0;
}
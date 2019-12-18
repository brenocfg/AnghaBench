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
struct ssp_data {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ssp_clean_pending_list (struct ssp_data*) ; 
 int /*<<< orphan*/  ssp_enable_mcu (struct ssp_data*,int) ; 
 int /*<<< orphan*/  ssp_toggle_mcu_reset_gpio (struct ssp_data*) ; 

__attribute__((used)) static void ssp_reset_mcu(struct ssp_data *data)
{
	ssp_enable_mcu(data, false);
	ssp_clean_pending_list(data);
	ssp_toggle_mcu_reset_gpio(data);
	ssp_enable_mcu(data, true);
}
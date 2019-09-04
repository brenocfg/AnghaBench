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
struct ti_emif_data {int dummy; } ;
struct platform_device {int dummy; } ;

/* Variables and functions */
 struct ti_emif_data* emif_instance ; 
 int /*<<< orphan*/  ti_emif_free_sram (struct ti_emif_data*) ; 

__attribute__((used)) static int ti_emif_remove(struct platform_device *pdev)
{
	struct ti_emif_data *emif_data = emif_instance;

	emif_instance = NULL;

	ti_emif_free_sram(emif_data);

	return 0;
}
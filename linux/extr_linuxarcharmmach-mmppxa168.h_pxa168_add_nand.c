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
struct pxa3xx_nand_platform_data {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  pxa168_device_nand ; 
 int pxa_register_device (int /*<<< orphan*/ *,struct pxa3xx_nand_platform_data*,int) ; 

__attribute__((used)) static inline int pxa168_add_nand(struct pxa3xx_nand_platform_data *info)
{
	return pxa_register_device(&pxa168_device_nand, info, sizeof(*info));
}
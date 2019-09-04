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
struct bgx {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  acpi_disabled ; 
 int bgx_init_acpi_phy (struct bgx*) ; 
 int bgx_init_of_phy (struct bgx*) ; 

__attribute__((used)) static int bgx_init_phy(struct bgx *bgx)
{
	if (!acpi_disabled)
		return bgx_init_acpi_phy(bgx);

	return bgx_init_of_phy(bgx);
}
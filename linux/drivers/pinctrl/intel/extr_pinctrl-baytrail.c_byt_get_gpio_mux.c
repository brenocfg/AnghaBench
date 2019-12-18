#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct byt_gpio {TYPE_1__* soc_data; } ;
struct TYPE_2__ {int /*<<< orphan*/  uid; } ;

/* Variables and functions */
 int /*<<< orphan*/  BYT_ALTER_GPIO_MUX ; 
 int /*<<< orphan*/  BYT_DEFAULT_GPIO_MUX ; 
 int /*<<< orphan*/  BYT_SCORE_ACPI_UID ; 
 int /*<<< orphan*/  BYT_SUS_ACPI_UID ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static u32 byt_get_gpio_mux(struct byt_gpio *vg, unsigned int offset)
{
	/* SCORE pin 92-93 */
	if (!strcmp(vg->soc_data->uid, BYT_SCORE_ACPI_UID) &&
	    offset >= 92 && offset <= 93)
		return BYT_ALTER_GPIO_MUX;

	/* SUS pin 11-21 */
	if (!strcmp(vg->soc_data->uid, BYT_SUS_ACPI_UID) &&
	    offset >= 11 && offset <= 21)
		return BYT_ALTER_GPIO_MUX;

	return BYT_DEFAULT_GPIO_MUX;
}
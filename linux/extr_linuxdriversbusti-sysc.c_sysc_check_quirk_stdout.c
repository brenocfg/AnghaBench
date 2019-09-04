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
struct TYPE_2__ {int quirks; } ;
struct sysc {TYPE_1__ cfg; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 int SYSC_QUIRK_NO_IDLE_ON_INIT ; 
 int SYSC_QUIRK_NO_RESET_ON_INIT ; 
 struct device_node* stdout_path ; 
 int /*<<< orphan*/  sysc_init_stdout_path (struct sysc*) ; 

__attribute__((used)) static void sysc_check_quirk_stdout(struct sysc *ddata,
				    struct device_node *np)
{
	sysc_init_stdout_path(ddata);
	if (np != stdout_path)
		return;

	ddata->cfg.quirks |= SYSC_QUIRK_NO_IDLE_ON_INIT |
				SYSC_QUIRK_NO_RESET_ON_INIT;
}
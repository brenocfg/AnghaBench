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
struct display_mode_lib {int project; int /*<<< orphan*/  ip; int /*<<< orphan*/  soc; } ;
typedef  enum dml_project { ____Placeholder_dml_project } dml_project ;

/* Variables and functions */
 int /*<<< orphan*/  set_ip_params (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  set_soc_bounding_box (int /*<<< orphan*/ *,int) ; 

void dml_init_instance(struct display_mode_lib *lib, enum dml_project project)
{
	if (lib->project != project) {
		set_soc_bounding_box(&lib->soc, project);
		set_ip_params(&lib->ip, project);
		lib->project = project;
	}
}
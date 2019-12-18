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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  enum dml_project { ____Placeholder_dml_project } dml_project ;

/* Variables and functions */
 int DML_PROJECT_NAVI10v2 ; 

__attribute__((used)) static enum dml_project get_dml_project_version(uint32_t hw_internal_rev)
{
	return DML_PROJECT_NAVI10v2;
}
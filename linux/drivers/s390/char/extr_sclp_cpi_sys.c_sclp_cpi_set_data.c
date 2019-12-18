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
typedef  int /*<<< orphan*/  u64 ;

/* Variables and functions */
 int check_string (char*,char const*) ; 
 int cpi_req () ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sclp_cpi_mutex ; 
 int /*<<< orphan*/  set_string (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  sysplex_name ; 
 int /*<<< orphan*/  system_level ; 
 int /*<<< orphan*/  system_name ; 
 int /*<<< orphan*/  system_type ; 

int sclp_cpi_set_data(const char *system, const char *sysplex, const char *type,
		      const u64 level)
{
	int rc;

	rc = check_string("system_name", system);
	if (rc)
		return rc;
	rc = check_string("sysplex_name", sysplex);
	if (rc)
		return rc;
	rc = check_string("system_type", type);
	if (rc)
		return rc;

	mutex_lock(&sclp_cpi_mutex);
	set_string(system_name, system);
	set_string(sysplex_name, sysplex);
	set_string(system_type, type);
	system_level = level;

	rc = cpi_req();
	mutex_unlock(&sclp_cpi_mutex);

	return rc;
}
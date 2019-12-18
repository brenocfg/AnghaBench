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
struct pqi_config_table_section_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pqi_firmware_features_mutex ; 
 int /*<<< orphan*/  pqi_init_firmware_features () ; 
 int /*<<< orphan*/  pqi_process_firmware_features (struct pqi_config_table_section_info*) ; 

__attribute__((used)) static void pqi_process_firmware_features_section(
	struct pqi_config_table_section_info *section_info)
{
	mutex_lock(&pqi_firmware_features_mutex);
	pqi_init_firmware_features();
	pqi_process_firmware_features(section_info);
	mutex_unlock(&pqi_firmware_features_mutex);
}
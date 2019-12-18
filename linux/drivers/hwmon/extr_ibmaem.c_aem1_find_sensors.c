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
struct aem_data {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  aem1_ro_sensors ; 
 int /*<<< orphan*/  aem1_rw_sensors ; 
 int aem_register_sensors (struct aem_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int aem1_find_sensors(struct aem_data *data)
{
	return aem_register_sensors(data, aem1_ro_sensors, aem1_rw_sensors);
}
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
struct aem_data {int ver_major; } ;

/* Variables and functions */
 int /*<<< orphan*/  update_aem_energy_one (struct aem_data*,int) ; 

__attribute__((used)) static void update_aem_energy(struct aem_data *data)
{
	update_aem_energy_one(data, 0);
	if (data->ver_major < 2)
		return;
	update_aem_energy_one(data, 1);
}
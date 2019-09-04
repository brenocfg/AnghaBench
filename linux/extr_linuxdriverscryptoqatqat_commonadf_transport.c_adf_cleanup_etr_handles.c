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
typedef  size_t uint32_t ;
struct adf_etr_data {int /*<<< orphan*/ * banks; } ;
struct adf_accel_dev {struct adf_etr_data* transport; } ;

/* Variables and functions */
 size_t GET_MAX_BANKS (struct adf_accel_dev*) ; 
 int /*<<< orphan*/  cleanup_bank (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void adf_cleanup_etr_handles(struct adf_accel_dev *accel_dev)
{
	struct adf_etr_data *etr_data = accel_dev->transport;
	uint32_t i, num_banks = GET_MAX_BANKS(accel_dev);

	for (i = 0; i < num_banks; i++)
		cleanup_bank(&etr_data->banks[i]);
}
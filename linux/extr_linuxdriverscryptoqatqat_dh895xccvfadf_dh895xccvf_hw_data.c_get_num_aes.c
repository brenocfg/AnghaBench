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
typedef  int /*<<< orphan*/  u32 ;
struct adf_hw_device_data {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADF_DH895XCCIOV_MAX_ACCELENGINES ; 

__attribute__((used)) static u32 get_num_aes(struct adf_hw_device_data *self)
{
	return ADF_DH895XCCIOV_MAX_ACCELENGINES;
}
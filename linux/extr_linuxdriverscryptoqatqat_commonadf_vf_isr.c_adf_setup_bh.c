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
struct adf_etr_data {TYPE_1__* banks; } ;
struct adf_accel_dev {struct adf_etr_data* transport; } ;
struct TYPE_2__ {int /*<<< orphan*/  resp_handler; } ;

/* Variables and functions */
 int /*<<< orphan*/  adf_response_handler ; 
 int /*<<< orphan*/  tasklet_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned long) ; 

__attribute__((used)) static int adf_setup_bh(struct adf_accel_dev *accel_dev)
{
	struct adf_etr_data *priv_data = accel_dev->transport;

	tasklet_init(&priv_data->banks[0].resp_handler, adf_response_handler,
		     (unsigned long)priv_data->banks);
	return 0;
}
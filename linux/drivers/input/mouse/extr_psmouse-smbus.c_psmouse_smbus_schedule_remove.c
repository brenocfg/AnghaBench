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
struct psmouse_smbus_removal_work {int /*<<< orphan*/  work; struct i2c_client* client; } ;
struct i2c_client {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct psmouse_smbus_removal_work* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  psmouse_smbus_remove_i2c_device ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void psmouse_smbus_schedule_remove(struct i2c_client *client)
{
	struct psmouse_smbus_removal_work *rwork;

	rwork = kzalloc(sizeof(*rwork), GFP_KERNEL);
	if (rwork) {
		INIT_WORK(&rwork->work, psmouse_smbus_remove_i2c_device);
		rwork->client = client;

		schedule_work(&rwork->work);
	}
}
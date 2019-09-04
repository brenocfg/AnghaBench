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
struct i2c_payloads {int /*<<< orphan*/  payloads; } ;

/* Variables and functions */
 int /*<<< orphan*/  dal_vector_destruct (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct i2c_payloads*) ; 

__attribute__((used)) static void dal_ddc_i2c_payloads_destroy(struct i2c_payloads **p)
{
	if (!p || !*p)
		return;
	dal_vector_destruct(&(*p)->payloads);
	kfree(*p);
	*p = NULL;

}
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
struct amdgpu_i2c_chan {int /*<<< orphan*/  adapter; int /*<<< orphan*/  has_aux; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i2c_del_adapter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct amdgpu_i2c_chan*) ; 

void amdgpu_i2c_destroy(struct amdgpu_i2c_chan *i2c)
{
	if (!i2c)
		return;
	WARN_ON(i2c->has_aux);
	i2c_del_adapter(&i2c->adapter);
	kfree(i2c);
}
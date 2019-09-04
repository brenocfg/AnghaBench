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
struct go7007 {int i2c_adapter_online; int /*<<< orphan*/  hw_lock; } ;

/* Variables and functions */
 scalar_t__ go7007_i2c_init (struct go7007*) ; 
 int go7007_load_encoder (struct go7007*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

int go7007_boot_encoder(struct go7007 *go, int init_i2c)
{
	int ret;

	mutex_lock(&go->hw_lock);
	ret = go7007_load_encoder(go);
	mutex_unlock(&go->hw_lock);
	if (ret < 0)
		return -1;
	if (!init_i2c)
		return 0;
	if (go7007_i2c_init(go) < 0)
		return -1;
	go->i2c_adapter_online = 1;
	return 0;
}
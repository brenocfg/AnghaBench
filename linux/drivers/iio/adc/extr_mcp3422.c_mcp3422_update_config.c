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
typedef  int /*<<< orphan*/  u8 ;
struct mcp3422 {int /*<<< orphan*/  lock; int /*<<< orphan*/  config; int /*<<< orphan*/  i2c; } ;

/* Variables and functions */
 int i2c_master_send (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int mcp3422_update_config(struct mcp3422 *adc, u8 newconfig)
{
	int ret;

	mutex_lock(&adc->lock);

	ret = i2c_master_send(adc->i2c, &newconfig, 1);
	if (ret > 0) {
		adc->config = newconfig;
		ret = 0;
	}

	mutex_unlock(&adc->lock);

	return ret;
}
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
struct mag3110_data {int /*<<< orphan*/  lock; int /*<<< orphan*/  client; } ;
typedef  int /*<<< orphan*/  __be16 ;

/* Variables and functions */
 int /*<<< orphan*/  MAG3110_OUT_X ; 
 int i2c_smbus_read_i2c_block_data (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int mag3110_request (struct mag3110_data*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int mag3110_read(struct mag3110_data *data, __be16 buf[3])
{
	int ret;

	mutex_lock(&data->lock);
	ret = mag3110_request(data);
	if (ret < 0) {
		mutex_unlock(&data->lock);
		return ret;
	}
	ret = i2c_smbus_read_i2c_block_data(data->client,
		MAG3110_OUT_X, 3 * sizeof(__be16), (u8 *) buf);
	mutex_unlock(&data->lock);

	return ret;
}
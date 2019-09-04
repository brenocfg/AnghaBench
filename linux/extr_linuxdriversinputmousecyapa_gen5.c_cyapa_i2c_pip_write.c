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
struct cyapa {int /*<<< orphan*/  client; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int EINVAL ; 
 int EIO ; 
 int i2c_master_send (int /*<<< orphan*/ ,int /*<<< orphan*/ *,size_t) ; 

ssize_t cyapa_i2c_pip_write(struct cyapa *cyapa, u8 *buf, size_t size)
{
	int ret;

	if (!buf || !size)
		return -EINVAL;

	ret = i2c_master_send(cyapa->client, buf, size);

	if (ret != size)
		return (ret < 0) ? ret : -EIO;

	return 0;
}
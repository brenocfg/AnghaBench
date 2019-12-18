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
 size_t CYAPA_REG_MAP_SIZE ; 
 int EINVAL ; 
 int EIO ; 
 int i2c_master_recv (int /*<<< orphan*/ ,int /*<<< orphan*/ *,size_t) ; 

ssize_t cyapa_i2c_pip_read(struct cyapa *cyapa, u8 *buf, size_t size)
{
	int ret;

	if (size == 0)
		return 0;

	if (!buf || size > CYAPA_REG_MAP_SIZE)
		return -EINVAL;

	ret = i2c_master_recv(cyapa->client, buf, size);

	if (ret != size)
		return (ret < 0) ? ret : -EIO;
	return size;
}
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
typedef  int /*<<< orphan*/  zd_addr_t ;
typedef  int /*<<< orphan*/  u32 ;
struct zd_chip {int /*<<< orphan*/  mutex; } ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int zd_ioread32v_locked (struct zd_chip*,int /*<<< orphan*/ *,int /*<<< orphan*/  const*,unsigned int) ; 

int zd_ioread32v(struct zd_chip *chip, const zd_addr_t *addresses,
	          u32 *values, unsigned int count)
{
	int r;

	mutex_lock(&chip->mutex);
	r = zd_ioread32v_locked(chip, values, addresses, count);
	mutex_unlock(&chip->mutex);
	return r;
}
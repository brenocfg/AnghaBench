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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct fsi_slave {int /*<<< orphan*/  link; int /*<<< orphan*/  master; int /*<<< orphan*/  id; } ;

/* Variables and functions */
 int fsi_master_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void const*,size_t) ; 
 int fsi_slave_calc_addr (struct fsi_slave*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int fsi_slave_handle_error (struct fsi_slave*,int,int /*<<< orphan*/ ,size_t) ; 
 int slave_retries ; 

int fsi_slave_write(struct fsi_slave *slave, uint32_t addr,
			const void *val, size_t size)
{
	uint8_t id = slave->id;
	int rc, err_rc, i;

	rc = fsi_slave_calc_addr(slave, &addr, &id);
	if (rc)
		return rc;

	for (i = 0; i < slave_retries; i++) {
		rc = fsi_master_write(slave->master, slave->link,
				id, addr, val, size);
		if (!rc)
			break;

		err_rc = fsi_slave_handle_error(slave, true, addr, size);
		if (err_rc)
			break;
	}

	return rc;
}
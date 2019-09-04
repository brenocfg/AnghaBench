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
struct fsi_master {int (* read ) (struct fsi_master*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,size_t) ;} ;

/* Variables and functions */
 int fsi_check_access (int /*<<< orphan*/ ,size_t) ; 
 int stub1 (struct fsi_master*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,size_t) ; 
 int /*<<< orphan*/  trace_fsi_master_read (struct fsi_master*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  trace_fsi_master_rw_result (struct fsi_master*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t,int,void*,int) ; 

__attribute__((used)) static int fsi_master_read(struct fsi_master *master, int link,
		uint8_t slave_id, uint32_t addr, void *val, size_t size)
{
	int rc;

	trace_fsi_master_read(master, link, slave_id, addr, size);

	rc = fsi_check_access(addr, size);
	if (!rc)
		rc = master->read(master, link, slave_id, addr, val, size);

	trace_fsi_master_rw_result(master, link, slave_id, addr, size,
			false, val, rc);

	return rc;
}
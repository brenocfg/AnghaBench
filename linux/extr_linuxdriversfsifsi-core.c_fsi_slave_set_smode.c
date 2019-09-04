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
typedef  int /*<<< orphan*/  uint32_t ;
struct fsi_slave {int /*<<< orphan*/  id; int /*<<< orphan*/  link; int /*<<< orphan*/  master; int /*<<< orphan*/  t_echo_delay; int /*<<< orphan*/  t_send_delay; } ;
typedef  int /*<<< orphan*/  data ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 scalar_t__ FSI_SLAVE_BASE ; 
 scalar_t__ FSI_SMODE ; 
 int /*<<< orphan*/  cpu_to_be32 (int /*<<< orphan*/ ) ; 
 int fsi_master_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  fsi_slave_smode (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int fsi_slave_set_smode(struct fsi_slave *slave)
{
	uint32_t smode;
	__be32 data;

	/* set our smode register with the slave ID field to 0; this enables
	 * extended slave addressing
	 */
	smode = fsi_slave_smode(slave->id, slave->t_send_delay, slave->t_echo_delay);
	data = cpu_to_be32(smode);

	return fsi_master_write(slave->master, slave->link, slave->id,
				FSI_SLAVE_BASE + FSI_SMODE,
				&data, sizeof(data));
}
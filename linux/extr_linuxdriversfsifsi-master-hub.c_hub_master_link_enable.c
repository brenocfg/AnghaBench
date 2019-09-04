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
struct fsi_master_hub {int /*<<< orphan*/  upstream; } ;
struct fsi_master {int dummy; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int /*<<< orphan*/  FSI_LINK_ENABLE_SETUP_TIME ; 
 scalar_t__ FSI_MENP0 ; 
 scalar_t__ FSI_MSENP0 ; 
 int /*<<< orphan*/  cpu_to_be32 (int) ; 
 int /*<<< orphan*/  fsi_device_read (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *,int) ; 
 int fsi_device_write (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  mdelay (int /*<<< orphan*/ ) ; 
 struct fsi_master_hub* to_fsi_master_hub (struct fsi_master*) ; 

__attribute__((used)) static int hub_master_link_enable(struct fsi_master *master, int link)
{
	struct fsi_master_hub *hub = to_fsi_master_hub(master);
	int idx, bit;
	__be32 reg;
	int rc;

	idx = link / 32;
	bit = link % 32;

	reg = cpu_to_be32(0x80000000 >> bit);

	rc = fsi_device_write(hub->upstream, FSI_MSENP0 + (4 * idx), &reg, 4);

	mdelay(FSI_LINK_ENABLE_SETUP_TIME);

	fsi_device_read(hub->upstream, FSI_MENP0 + (4 * idx), &reg, 4);

	return rc;
}
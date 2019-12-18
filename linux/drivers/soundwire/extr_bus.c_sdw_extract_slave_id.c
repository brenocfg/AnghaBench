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
typedef  int u64 ;
struct sdw_slave_id {int sdw_version; int unique_id; int mfg_id; int part_id; int class_id; } ;
struct sdw_bus {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int GENMASK (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int,...) ; 

void sdw_extract_slave_id(struct sdw_bus *bus,
			  u64 addr, struct sdw_slave_id *id)
{
	dev_dbg(bus->dev, "SDW Slave Addr: %llx\n", addr);

	/*
	 * Spec definition
	 *   Register		Bit	Contents
	 *   DevId_0 [7:4]	47:44	sdw_version
	 *   DevId_0 [3:0]	43:40	unique_id
	 *   DevId_1		39:32	mfg_id [15:8]
	 *   DevId_2		31:24	mfg_id [7:0]
	 *   DevId_3		23:16	part_id [15:8]
	 *   DevId_4		15:08	part_id [7:0]
	 *   DevId_5		07:00	class_id
	 */
	id->sdw_version = (addr >> 44) & GENMASK(3, 0);
	id->unique_id = (addr >> 40) & GENMASK(3, 0);
	id->mfg_id = (addr >> 24) & GENMASK(15, 0);
	id->part_id = (addr >> 8) & GENMASK(15, 0);
	id->class_id = addr & GENMASK(7, 0);

	dev_dbg(bus->dev,
		"SDW Slave class_id %x, part_id %x, mfg_id %x, unique_id %x, version %x\n",
				id->class_id, id->part_id, id->mfg_id,
				id->unique_id, id->sdw_version);
}
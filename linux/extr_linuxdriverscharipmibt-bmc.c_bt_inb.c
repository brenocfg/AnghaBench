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
typedef  scalar_t__ uint32_t ;
typedef  int /*<<< orphan*/  u8 ;
struct bt_bmc {scalar_t__ offset; int /*<<< orphan*/  map; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN (int,char*,int) ; 
 int regmap_read (int /*<<< orphan*/ ,scalar_t__,scalar_t__*) ; 

__attribute__((used)) static u8 bt_inb(struct bt_bmc *bt_bmc, int reg)
{
	uint32_t val = 0;
	int rc;

	rc = regmap_read(bt_bmc->map, bt_bmc->offset + reg, &val);
	WARN(rc != 0, "regmap_read() failed: %d\n", rc);

	return rc == 0 ? (u8) val : 0;
}
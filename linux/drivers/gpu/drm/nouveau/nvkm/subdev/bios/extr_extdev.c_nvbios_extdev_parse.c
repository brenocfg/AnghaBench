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
typedef  int /*<<< orphan*/  u16 ;
struct nvkm_bios {int dummy; } ;
struct nvbios_extdev_func {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  extdev_parse_entry (struct nvkm_bios*,int /*<<< orphan*/ ,struct nvbios_extdev_func*) ; 
 int /*<<< orphan*/  nvbios_extdev_entry (struct nvkm_bios*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int
nvbios_extdev_parse(struct nvkm_bios *bios, int idx,
		    struct nvbios_extdev_func *func)
{
	u8 ver, len;
	u16 entry;

	if (!(entry = nvbios_extdev_entry(bios, idx, &ver, &len)))
		return -EINVAL;

	extdev_parse_entry(bios, entry, func);
	return 0;
}
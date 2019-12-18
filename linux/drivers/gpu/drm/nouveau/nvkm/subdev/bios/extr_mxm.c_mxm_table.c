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
typedef  int u8 ;
typedef  int u16 ;
struct nvkm_subdev {int dummy; } ;
struct nvkm_bios {struct nvkm_subdev subdev; } ;
struct bit_entry {int version; int length; int offset; } ;

/* Variables and functions */
 scalar_t__ bit_entry (struct nvkm_bios*,char,struct bit_entry*) ; 
 int /*<<< orphan*/  nvkm_debug (struct nvkm_subdev*,char*) ; 
 int /*<<< orphan*/  nvkm_warn (struct nvkm_subdev*,char*,int,int) ; 

u16
mxm_table(struct nvkm_bios *bios, u8 *ver, u8 *hdr)
{
	struct nvkm_subdev *subdev = &bios->subdev;
	struct bit_entry x;

	if (bit_entry(bios, 'x', &x)) {
		nvkm_debug(subdev, "BIT 'x' table not present\n");
		return 0x0000;
	}

	*ver = x.version;
	*hdr = x.length;
	if (*ver != 1 || *hdr < 3) {
		nvkm_warn(subdev, "BIT 'x' table %d/%d unknown\n", *ver, *hdr);
		return 0x0000;
	}

	return x.offset;
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct vblk_disk {int /*<<< orphan*/  disk_id; int /*<<< orphan*/  alt_name; } ;
struct TYPE_2__ {struct vblk_disk disk; } ;
struct vblk {TYPE_1__ vblk; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 scalar_t__ VBLK_SIZE_DSK3 ; 
 int get_unaligned_be32 (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  ldm_get_vstr (int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int) ; 
 int ldm_relative (int /*<<< orphan*/  const*,int,int,int) ; 
 scalar_t__ uuid_parse (int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool ldm_parse_dsk3 (const u8 *buffer, int buflen, struct vblk *vb)
{
	int r_objid, r_name, r_diskid, r_altname, len;
	struct vblk_disk *disk;

	BUG_ON (!buffer || !vb);

	r_objid   = ldm_relative (buffer, buflen, 0x18, 0);
	r_name    = ldm_relative (buffer, buflen, 0x18, r_objid);
	r_diskid  = ldm_relative (buffer, buflen, 0x18, r_name);
	r_altname = ldm_relative (buffer, buflen, 0x18, r_diskid);
	len = r_altname;
	if (len < 0)
		return false;

	len += VBLK_SIZE_DSK3;
	if (len != get_unaligned_be32(buffer + 0x14))
		return false;

	disk = &vb->vblk.disk;
	ldm_get_vstr (buffer + 0x18 + r_diskid, disk->alt_name,
		sizeof (disk->alt_name));
	if (uuid_parse(buffer + 0x19 + r_name, &disk->disk_id))
		return false;

	return true;
}
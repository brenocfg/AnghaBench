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
typedef  scalar_t__ u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct esas2r_pc_image {scalar_t__ checksum; scalar_t__ pnp_offset; scalar_t__ header_offset; } ;
struct esas2r_flash_img {struct esas2r_component_header* cmp_hdr; } ;
struct esas2r_component_header {int image_offset; int length; } ;
struct esas2r_boot_header {int /*<<< orphan*/  device_id; } ;
struct esas2r_adapter {TYPE_1__* pcid; } ;
struct TYPE_2__ {int /*<<< orphan*/  subsystem_device; int /*<<< orphan*/  subsystem_vendor; int /*<<< orphan*/  device; } ;

/* Variables and functions */
 size_t CH_IT_BIOS ; 
 int /*<<< orphan*/  MAKEDWORD (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_le16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_le32 (int /*<<< orphan*/ ) ; 
 scalar_t__ esas2r_calc_byte_cksum (scalar_t__*,int,int /*<<< orphan*/ ) ; 
 int le16_to_cpu (scalar_t__) ; 

__attribute__((used)) static void fix_bios(struct esas2r_adapter *a, struct esas2r_flash_img *fi)
{
	struct esas2r_component_header *ch = &fi->cmp_hdr[CH_IT_BIOS];
	struct esas2r_pc_image *pi;
	struct esas2r_boot_header *bh;

	pi = (struct esas2r_pc_image *)((u8 *)fi + ch->image_offset);
	bh =
		(struct esas2r_boot_header *)((u8 *)pi +
					      le16_to_cpu(pi->header_offset));
	bh->device_id = cpu_to_le16(a->pcid->device);

	/* Recalculate the checksum in the PNP header if there  */
	if (pi->pnp_offset) {
		u8 *pnp_header_bytes =
			((u8 *)pi + le16_to_cpu(pi->pnp_offset));

		/* Identifier - dword that starts at byte 10 */
		*((u32 *)&pnp_header_bytes[10]) =
			cpu_to_le32(MAKEDWORD(a->pcid->subsystem_vendor,
					      a->pcid->subsystem_device));

		/* Checksum - byte 9 */
		pnp_header_bytes[9] -= esas2r_calc_byte_cksum(pnp_header_bytes,
							      32, 0);
	}

	/* Recalculate the checksum needed by the PC */
	pi->checksum = pi->checksum -
		       esas2r_calc_byte_cksum((u8 *)pi, ch->length, 0);
}
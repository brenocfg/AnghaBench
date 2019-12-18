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
typedef  int u32 ;
struct esas2r_flash_img {struct esas2r_component_header* cmp_hdr; } ;
struct esas2r_efi_image {int /*<<< orphan*/  header_offset; } ;
struct esas2r_component_header {int length; int image_offset; } ;
struct esas2r_boot_header {int /*<<< orphan*/  image_length; int /*<<< orphan*/  device_id; } ;
struct esas2r_adapter {TYPE_1__* pcid; } ;
struct TYPE_2__ {int /*<<< orphan*/  device; } ;

/* Variables and functions */
 size_t CH_IT_EFI ; 
 int /*<<< orphan*/  cpu_to_le16 (int /*<<< orphan*/ ) ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void fix_efi(struct esas2r_adapter *a, struct esas2r_flash_img *fi)
{
	struct esas2r_component_header *ch = &fi->cmp_hdr[CH_IT_EFI];
	u32 len = ch->length;
	u32 offset = ch->image_offset;
	struct esas2r_efi_image *ei;
	struct esas2r_boot_header *bh;

	while (len) {
		u32 thislen;

		ei = (struct esas2r_efi_image *)((u8 *)fi + offset);
		bh = (struct esas2r_boot_header *)((u8 *)ei +
						   le16_to_cpu(
							   ei->header_offset));
		bh->device_id = cpu_to_le16(a->pcid->device);
		thislen = (u32)le16_to_cpu(bh->image_length) * 512;

		if (thislen > len)
			break;

		len -= thislen;
		offset += thislen;
	}
}
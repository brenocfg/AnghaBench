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
typedef  void* u64 ;
typedef  void* u32 ;
struct screen_info {int lfb_depth; int red_size; int red_pos; int green_size; int green_pos; int blue_size; int rsvd_size; int rsvd_pos; scalar_t__ blue_pos; void* lfb_height; void* lfb_width; int /*<<< orphan*/  orig_video_isVGA; } ;
typedef  int /*<<< orphan*/  efi_uga_draw_protocol_t ;
typedef  scalar_t__ efi_status_t ;
typedef  int /*<<< orphan*/  efi_guid_t ;

/* Variables and functions */
 int /*<<< orphan*/  EFI_LOADER_DATA ; 
 int /*<<< orphan*/  EFI_LOCATE_BY_PROTOCOL ; 
 int /*<<< orphan*/  EFI_PCI_IO_PROTOCOL_GUID ; 
 scalar_t__ EFI_SUCCESS ; 
 int /*<<< orphan*/  VIDEO_TYPE_EFI ; 
 int /*<<< orphan*/  allocate_pool ; 
 scalar_t__ efi_call_early (int /*<<< orphan*/ ,...) ; 
 scalar_t__ efi_call_proto (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,void**,void**,void**,void**) ; 
 scalar_t__ efi_is_64bit () ; 
 int /*<<< orphan*/  efi_uga_draw_protocol ; 
 int /*<<< orphan*/  free_pool ; 
 int /*<<< orphan*/  get_mode ; 
 int /*<<< orphan*/  handle_protocol ; 
 int /*<<< orphan*/  locate_handle ; 

__attribute__((used)) static efi_status_t
setup_uga(struct screen_info *si, efi_guid_t *uga_proto, unsigned long size)
{
	efi_status_t status;
	u32 width, height;
	void **uga_handle = NULL;
	efi_uga_draw_protocol_t *uga = NULL, *first_uga;
	unsigned long nr_ugas;
	int i;

	status = efi_call_early(allocate_pool, EFI_LOADER_DATA,
				size, (void **)&uga_handle);
	if (status != EFI_SUCCESS)
		return status;

	status = efi_call_early(locate_handle,
				EFI_LOCATE_BY_PROTOCOL,
				uga_proto, NULL, &size, uga_handle);
	if (status != EFI_SUCCESS)
		goto free_handle;

	height = 0;
	width = 0;

	first_uga = NULL;
	nr_ugas = size / (efi_is_64bit() ? sizeof(u64) : sizeof(u32));
	for (i = 0; i < nr_ugas; i++) {
		efi_guid_t pciio_proto = EFI_PCI_IO_PROTOCOL_GUID;
		u32 w, h, depth, refresh;
		void *pciio;
		unsigned long handle = efi_is_64bit() ? ((u64 *)uga_handle)[i]
						      : ((u32 *)uga_handle)[i];

		status = efi_call_early(handle_protocol, handle,
					uga_proto, (void **)&uga);
		if (status != EFI_SUCCESS)
			continue;

		pciio = NULL;
		efi_call_early(handle_protocol, handle, &pciio_proto, &pciio);

		status = efi_call_proto(efi_uga_draw_protocol, get_mode, uga,
					&w, &h, &depth, &refresh);
		if (status == EFI_SUCCESS && (!first_uga || pciio)) {
			width = w;
			height = h;

			/*
			 * Once we've found a UGA supporting PCIIO,
			 * don't bother looking any further.
			 */
			if (pciio)
				break;

			first_uga = uga;
		}
	}

	if (!width && !height)
		goto free_handle;

	/* EFI framebuffer */
	si->orig_video_isVGA	= VIDEO_TYPE_EFI;

	si->lfb_depth		= 32;
	si->lfb_width		= width;
	si->lfb_height		= height;

	si->red_size		= 8;
	si->red_pos		= 16;
	si->green_size		= 8;
	si->green_pos		= 8;
	si->blue_size		= 8;
	si->blue_pos		= 0;
	si->rsvd_size		= 8;
	si->rsvd_pos		= 24;

free_handle:
	efi_call_early(free_pool, uga_handle);

	return status;
}
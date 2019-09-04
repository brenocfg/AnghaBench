#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
typedef  int u16 ;
struct TYPE_4__ {int lfb_linelength; int lfb_height; } ;
struct TYPE_6__ {TYPE_1__ screen_info; } ;
struct TYPE_5__ {int height; } ;

/* Variables and functions */
 TYPE_3__ boot_params ; 
 unsigned long* early_efi_map (int,int) ; 
 int /*<<< orphan*/  early_efi_unmap (unsigned long*,int) ; 
 TYPE_2__* font ; 
 int /*<<< orphan*/  memmove (unsigned long*,unsigned long*,int) ; 

__attribute__((used)) static void early_efi_scroll_up(void)
{
	unsigned long *dst, *src;
	u16 len;
	u32 i, height;

	len = boot_params.screen_info.lfb_linelength;
	height = boot_params.screen_info.lfb_height;

	for (i = 0; i < height - font->height; i++) {
		dst = early_efi_map(i*len, len);
		if (!dst)
			return;

		src = early_efi_map((i + font->height) * len, len);
		if (!src) {
			early_efi_unmap(dst, len);
			return;
		}

		memmove(dst, src, len);

		early_efi_unmap(src, len);
		early_efi_unmap(dst, len);
	}
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  unsigned int u16 ;
struct TYPE_3__ {unsigned int lfb_linelength; } ;
struct TYPE_4__ {TYPE_1__ screen_info; } ;

/* Variables and functions */
 TYPE_2__ boot_params ; 
 unsigned long* early_efi_map (unsigned int,unsigned int) ; 
 int /*<<< orphan*/  early_efi_unmap (unsigned long*,unsigned int) ; 
 int /*<<< orphan*/  memset (unsigned long*,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static void early_efi_clear_scanline(unsigned int y)
{
	unsigned long *dst;
	u16 len;

	len = boot_params.screen_info.lfb_linelength;
	dst = early_efi_map(y*len, len);
	if (!dst)
		return;

	memset(dst, 0, len);
	early_efi_unmap(dst, len);
}
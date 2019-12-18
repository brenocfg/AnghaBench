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
typedef  int u16 ;
struct wl3501_card {scalar_t__ base_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  WL3501_BSS_SPAGE0 ; 
 int /*<<< orphan*/  WL3501_BSS_SPAGE1 ; 
 scalar_t__ WL3501_NIC_IODPA ; 
 scalar_t__ WL3501_NIC_LMAH ; 
 scalar_t__ WL3501_NIC_LMAL ; 
 int /*<<< orphan*/  wl3501_outb (int,scalar_t__) ; 
 int /*<<< orphan*/  wl3501_outsb (scalar_t__,void*,int) ; 
 int /*<<< orphan*/  wl3501_switch_page (struct wl3501_card*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void wl3501_set_to_wla(struct wl3501_card *this, u16 dest, void *src,
			      int size)
{
	/* switch to SRAM Page 0 */
	wl3501_switch_page(this, (dest & 0x8000) ? WL3501_BSS_SPAGE1 :
						   WL3501_BSS_SPAGE0);
	/* set LMAL and LMAH */
	wl3501_outb(dest & 0xff, this->base_addr + WL3501_NIC_LMAL);
	wl3501_outb(((dest >> 8) & 0x7f), this->base_addr + WL3501_NIC_LMAH);

	/* rep out to Port A */
	wl3501_outsb(this->base_addr + WL3501_NIC_IODPA, src, size);
}
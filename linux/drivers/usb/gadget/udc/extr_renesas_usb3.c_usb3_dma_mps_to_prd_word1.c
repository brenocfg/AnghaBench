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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_2__ {int maxpacket; } ;
struct renesas_usb3_ep {TYPE_1__ ep; } ;

/* Variables and functions */
 int /*<<< orphan*/  USB3_PRD1_MPS_1024 ; 
 int /*<<< orphan*/  USB3_PRD1_MPS_16 ; 
 int /*<<< orphan*/  USB3_PRD1_MPS_32 ; 
 int /*<<< orphan*/  USB3_PRD1_MPS_512 ; 
 int /*<<< orphan*/  USB3_PRD1_MPS_64 ; 
 int /*<<< orphan*/  USB3_PRD1_MPS_8 ; 
 int /*<<< orphan*/  USB3_PRD1_MPS_RESERVED ; 

__attribute__((used)) static u32 usb3_dma_mps_to_prd_word1(struct renesas_usb3_ep *usb3_ep)
{
	switch (usb3_ep->ep.maxpacket) {
	case 8:
		return USB3_PRD1_MPS_8;
	case 16:
		return USB3_PRD1_MPS_16;
	case 32:
		return USB3_PRD1_MPS_32;
	case 64:
		return USB3_PRD1_MPS_64;
	case 512:
		return USB3_PRD1_MPS_512;
	case 1024:
		return USB3_PRD1_MPS_1024;
	default:
		return USB3_PRD1_MPS_RESERVED;
	}
}
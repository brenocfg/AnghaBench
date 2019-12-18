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
struct nvidia_par {scalar_t__ PDIO0; scalar_t__ PDIO; scalar_t__ PRAMDAC0; scalar_t__ PRAMDAC; scalar_t__ PCRTC0; scalar_t__ PCRTC; scalar_t__ PCIO0; scalar_t__ PCIO; } ;

/* Variables and functions */

__attribute__((used)) static void NVSelectHeadRegisters(struct nvidia_par *par, int head)
{
	if (head) {
		par->PCIO = par->PCIO0 + 0x2000;
		par->PCRTC = par->PCRTC0 + 0x800;
		par->PRAMDAC = par->PRAMDAC0 + 0x800;
		par->PDIO = par->PDIO0 + 0x2000;
	} else {
		par->PCIO = par->PCIO0;
		par->PCRTC = par->PCRTC0;
		par->PRAMDAC = par->PRAMDAC0;
		par->PDIO = par->PDIO0;
	}
}
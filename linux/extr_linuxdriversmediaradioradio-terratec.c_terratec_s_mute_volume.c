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
struct radio_isa_card {scalar_t__ io; } ;

/* Variables and functions */
 int /*<<< orphan*/  outb (int,scalar_t__) ; 

__attribute__((used)) static int terratec_s_mute_volume(struct radio_isa_card *isa, bool mute, int vol)
{
	int i;

	if (mute)
		vol = 0;
	vol = vol + (vol * 32); /* change both channels */
	for (i = 0; i < 8; i++) {
		if (vol & (0x80 >> i))
			outb(0x80, isa->io + 1);
		else
			outb(0x00, isa->io + 1);
	}
	return 0;
}
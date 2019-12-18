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
struct atkbd {int emul; scalar_t__ translated; } ;

/* Variables and functions */

__attribute__((used)) static unsigned int atkbd_oqo_01plus_scancode_fixup(struct atkbd *atkbd,
						    unsigned int code)
{
	if (atkbd->translated && atkbd->emul == 1 &&
	    (code == 0x64 || code == 0x65 || code == 0x66)) {
		atkbd->emul = 0;
		code |= 0x80;
	}

	return code;
}
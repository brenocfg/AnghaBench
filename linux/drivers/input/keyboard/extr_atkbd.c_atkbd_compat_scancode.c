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
struct atkbd {int set; int emul; } ;

/* Variables and functions */

__attribute__((used)) static unsigned int atkbd_compat_scancode(struct atkbd *atkbd, unsigned int code)
{
	if (atkbd->set == 3) {
		if (atkbd->emul == 1)
			code |= 0x100;
        } else {
		code = (code & 0x7f) | ((code & 0x80) << 1);
		if (atkbd->emul == 1)
			code |= 0x80;
	}

	return code;
}
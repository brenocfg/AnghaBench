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
typedef  int u_char ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  dac_reg ; 
 int /*<<< orphan*/  dac_val ; 
 int depth ; 
 int /*<<< orphan*/  outb_p (unsigned int,int /*<<< orphan*/ ) ; 
 scalar_t__ pmi_setpal ; 
 scalar_t__ vga_compat ; 

__attribute__((used)) static int vesa_setpalette(int regno, unsigned red, unsigned green,
			    unsigned blue)
{
	int shift = 16 - depth;
	int err = -EINVAL;

/*
 * Try VGA registers first...
 */
	if (vga_compat) {
		outb_p(regno,       dac_reg);
		outb_p(red   >> shift, dac_val);
		outb_p(green >> shift, dac_val);
		outb_p(blue  >> shift, dac_val);
		err = 0;
	}

#ifdef __i386__
/*
 * Fallback to the PMI....
 */
	if (err && pmi_setpal) {
		struct { u_char blue, green, red, pad; } entry;

		entry.red   = red   >> shift;
		entry.green = green >> shift;
		entry.blue  = blue  >> shift;
		entry.pad   = 0;
	        __asm__ __volatile__(
                "call *(%%esi)"
                : /* no return value */
                : "a" (0x4f09),         /* EAX */
                  "b" (0),              /* EBX */
                  "c" (1),              /* ECX */
                  "d" (regno),          /* EDX */
                  "D" (&entry),         /* EDI */
                  "S" (&pmi_pal));      /* ESI */
		err = 0;
	}
#endif

	return err;
}
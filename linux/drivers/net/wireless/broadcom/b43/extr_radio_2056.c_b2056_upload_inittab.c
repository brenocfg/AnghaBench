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
typedef  unsigned int u16 ;
struct b43_wldev {int dummy; } ;
struct b2056_inittab_entry {int flags; unsigned int ghz5; unsigned int ghz2; } ;

/* Variables and functions */
 int B2056_INITTAB_ENTRY_OK ; 
 int B2056_INITTAB_UPLOAD ; 
 int /*<<< orphan*/  b43_radio_write (struct b43_wldev*,unsigned int,unsigned int) ; 

__attribute__((used)) static void b2056_upload_inittab(struct b43_wldev *dev, bool ghz5,
				 bool ignore_uploadflag, u16 routing,
				 const struct b2056_inittab_entry *e,
				 unsigned int length)
{
	unsigned int i;
	u16 value;

	for (i = 0; i < length; i++, e++) {
		if (!(e->flags & B2056_INITTAB_ENTRY_OK))
			continue;
		if ((e->flags & B2056_INITTAB_UPLOAD) || ignore_uploadflag) {
			if (ghz5)
				value = e->ghz5;
			else
				value = e->ghz2;
			b43_radio_write(dev, routing | i, value);
		}
	}
}
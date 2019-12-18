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
typedef  int /*<<< orphan*/  u8 ;
struct b43_wldev {int /*<<< orphan*/  wl; } ;
typedef  int /*<<< orphan*/  s16 ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int b43_tssi2dbm_entry (int /*<<< orphan*/ *,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  b43err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * kmalloc (int,int /*<<< orphan*/ ) ; 

u8 *b43_generate_dyn_tssi2dbm_tab(struct b43_wldev *dev,
				  s16 pab0, s16 pab1, s16 pab2)
{
	unsigned int i;
	u8 *tab;
	int err;

	tab = kmalloc(64, GFP_KERNEL);
	if (!tab) {
		b43err(dev->wl, "Could not allocate memory "
		       "for tssi2dbm table\n");
		return NULL;
	}
	for (i = 0; i < 64; i++) {
		err = b43_tssi2dbm_entry(tab, i, pab0, pab1, pab2);
		if (err) {
			b43err(dev->wl, "Could not generate "
			       "tssi2dBm table\n");
			kfree(tab);
			return NULL;
		}
	}

	return tab;
}
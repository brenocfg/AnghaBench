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
struct TYPE_4__ {unsigned long priv; int /*<<< orphan*/  data_read; int /*<<< orphan*/  name; } ;
struct b43_wl {int rng_initialized; TYPE_2__ rng; int /*<<< orphan*/  rng_name; TYPE_1__* hw; } ;
struct TYPE_3__ {int /*<<< orphan*/  wiphy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 char* KBUILD_MODNAME ; 
 int /*<<< orphan*/  b43_rng_read ; 
 int /*<<< orphan*/  b43err (struct b43_wl*,char*,int) ; 
 int hwrng_register (TYPE_2__*) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char*,char*) ; 
 char* wiphy_name (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int b43_rng_init(struct b43_wl *wl)
{
	int err = 0;

#ifdef CONFIG_B43_HWRNG
	snprintf(wl->rng_name, ARRAY_SIZE(wl->rng_name),
		 "%s_%s", KBUILD_MODNAME, wiphy_name(wl->hw->wiphy));
	wl->rng.name = wl->rng_name;
	wl->rng.data_read = b43_rng_read;
	wl->rng.priv = (unsigned long)wl;
	wl->rng_initialized = true;
	err = hwrng_register(&wl->rng);
	if (err) {
		wl->rng_initialized = false;
		b43err(wl, "Failed to register the random "
		       "number generator (%d)\n", err);
	}
#endif /* CONFIG_B43_HWRNG */

	return err;
}
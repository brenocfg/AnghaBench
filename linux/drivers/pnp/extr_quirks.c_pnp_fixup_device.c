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
struct pnp_fixup {int /*<<< orphan*/  (* quirk_function ) (struct pnp_dev*) ;scalar_t__* id; } ;
struct pnp_dev {int /*<<< orphan*/  dev; int /*<<< orphan*/  id; } ;

/* Variables and functions */
 int /*<<< orphan*/  compare_pnp_id (int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  pnp_dbg (int /*<<< orphan*/ *,char*,scalar_t__*,int /*<<< orphan*/  (*) (struct pnp_dev*)) ; 
 struct pnp_fixup* pnp_fixups ; 
 int /*<<< orphan*/  stub1 (struct pnp_dev*) ; 

void pnp_fixup_device(struct pnp_dev *dev)
{
	struct pnp_fixup *f;

	for (f = pnp_fixups; *f->id; f++) {
		if (!compare_pnp_id(dev->id, f->id))
			continue;
		pnp_dbg(&dev->dev, "%s: calling %pS\n", f->id,
			f->quirk_function);
		f->quirk_function(dev);
	}
}
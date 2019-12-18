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
struct ssb_init_invariants {int /*<<< orphan*/  has_cardbus_slot; int /*<<< orphan*/  sprom; int /*<<< orphan*/  boardinfo; } ;
struct ssb_bus {int /*<<< orphan*/  has_cardbus_slot; int /*<<< orphan*/  sprom; int /*<<< orphan*/  boardinfo; } ;
typedef  int (* ssb_invariants_func_t ) (struct ssb_bus*,struct ssb_init_invariants*) ;
typedef  int /*<<< orphan*/  iv ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memset (struct ssb_init_invariants*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int ssb_fetch_invariants(struct ssb_bus *bus,
				ssb_invariants_func_t get_invariants)
{
	struct ssb_init_invariants iv;
	int err;

	memset(&iv, 0, sizeof(iv));
	err = get_invariants(bus, &iv);
	if (err)
		goto out;
	memcpy(&bus->boardinfo, &iv.boardinfo, sizeof(iv.boardinfo));
	memcpy(&bus->sprom, &iv.sprom, sizeof(iv.sprom));
	bus->has_cardbus_slot = iv.has_cardbus_slot;
out:
	return err;
}
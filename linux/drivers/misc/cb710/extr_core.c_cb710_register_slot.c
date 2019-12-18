#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  release; int /*<<< orphan*/ * parent; } ;
struct TYPE_7__ {char const* name; TYPE_2__ dev; int /*<<< orphan*/  id; } ;
struct cb710_slot {unsigned int iobase; TYPE_3__ pdev; } ;
struct cb710_chip {int slots; unsigned int iobase; unsigned int slot_mask; int /*<<< orphan*/  slot_refs_count; TYPE_1__* pdev; int /*<<< orphan*/  platform_id; struct cb710_slot* slot; } ;
struct TYPE_5__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cb710_chip_dev (struct cb710_chip*) ; 
 int /*<<< orphan*/  cb710_release_slot ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,char const*,int /*<<< orphan*/ ,int,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  platform_device_put (TYPE_3__*) ; 
 int platform_device_register (TYPE_3__*) ; 
 int /*<<< orphan*/  smp_wmb () ; 

__attribute__((used)) static int cb710_register_slot(struct cb710_chip *chip,
	unsigned slot_mask, unsigned io_offset, const char *name)
{
	int nr = chip->slots;
	struct cb710_slot *slot = &chip->slot[nr];
	int err;

	dev_dbg(cb710_chip_dev(chip),
		"register: %s.%d; slot %d; mask %d; IO offset: 0x%02X\n",
		name, chip->platform_id, nr, slot_mask, io_offset);

	/* slot->irq_handler == NULL here; this needs to be
	 * seen before platform_device_register() */
	++chip->slots;
	smp_wmb();

	slot->iobase = chip->iobase + io_offset;
	slot->pdev.name = name;
	slot->pdev.id = chip->platform_id;
	slot->pdev.dev.parent = &chip->pdev->dev;
	slot->pdev.dev.release = cb710_release_slot;

	err = platform_device_register(&slot->pdev);

#ifdef CONFIG_CB710_DEBUG_ASSUMPTIONS
	atomic_inc(&chip->slot_refs_count);
#endif

	if (err) {
		/* device_initialize() called from platform_device_register()
		 * wants this on error path */
		platform_device_put(&slot->pdev);

		/* slot->irq_handler == NULL here anyway, so no lock needed */
		--chip->slots;
		return err;
	}

	chip->slot_mask |= slot_mask;

	return 0;
}
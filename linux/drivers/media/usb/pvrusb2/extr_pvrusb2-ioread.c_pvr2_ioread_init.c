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
struct pvr2_ioread {int /*<<< orphan*/ * buffer_storage; int /*<<< orphan*/  mutex; int /*<<< orphan*/ * stream; } ;

/* Variables and functions */
 unsigned int BUFFER_COUNT ; 
 int /*<<< orphan*/  BUFFER_SIZE ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kmalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int pvr2_ioread_init(struct pvr2_ioread *cp)
{
	unsigned int idx;

	cp->stream = NULL;
	mutex_init(&cp->mutex);

	for (idx = 0; idx < BUFFER_COUNT; idx++) {
		cp->buffer_storage[idx] = kmalloc(BUFFER_SIZE,GFP_KERNEL);
		if (!(cp->buffer_storage[idx])) break;
	}

	if (idx < BUFFER_COUNT) {
		// An allocation appears to have failed
		for (idx = 0; idx < BUFFER_COUNT; idx++) {
			if (!(cp->buffer_storage[idx])) continue;
			kfree(cp->buffer_storage[idx]);
		}
		return -ENOMEM;
	}
	return 0;
}
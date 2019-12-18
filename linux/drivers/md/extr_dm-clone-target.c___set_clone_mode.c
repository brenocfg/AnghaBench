#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct clone {TYPE_1__* ti; int /*<<< orphan*/  mode; int /*<<< orphan*/  cmd; } ;
typedef  enum clone_metadata_mode { ____Placeholder_clone_metadata_mode } clone_metadata_mode ;
struct TYPE_2__ {int /*<<< orphan*/  table; } ;

/* Variables and functions */
#define  CM_FAIL 130 
#define  CM_READ_ONLY 129 
#define  CM_WRITE 128 
 int /*<<< orphan*/  DMINFO (char*,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  WRITE_ONCE (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  clone_device_name (struct clone*) ; 
 int /*<<< orphan*/  dm_clone_metadata_set_read_only (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dm_clone_metadata_set_read_write (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dm_table_event (int /*<<< orphan*/ ) ; 
 int get_clone_mode (struct clone*) ; 

__attribute__((used)) static void __set_clone_mode(struct clone *clone, enum clone_metadata_mode new_mode)
{
	const char *descs[] = {
		"read-write",
		"read-only",
		"fail"
	};

	enum clone_metadata_mode old_mode = get_clone_mode(clone);

	/* Never move out of fail mode */
	if (old_mode == CM_FAIL)
		new_mode = CM_FAIL;

	switch (new_mode) {
	case CM_FAIL:
	case CM_READ_ONLY:
		dm_clone_metadata_set_read_only(clone->cmd);
		break;

	case CM_WRITE:
		dm_clone_metadata_set_read_write(clone->cmd);
		break;
	}

	WRITE_ONCE(clone->mode, new_mode);

	if (new_mode != old_mode) {
		dm_table_event(clone->ti->table);
		DMINFO("%s: Switching to %s mode", clone_device_name(clone),
		       descs[(int)new_mode]);
	}
}
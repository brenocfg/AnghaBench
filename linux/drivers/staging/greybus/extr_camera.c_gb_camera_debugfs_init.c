#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct gb_connection {TYPE_1__* intf; } ;
struct gb_camera_debugfs_entry {int /*<<< orphan*/  mask; int /*<<< orphan*/  name; } ;
struct TYPE_7__ {int /*<<< orphan*/  root; TYPE_4__* buffers; } ;
struct gb_camera {TYPE_3__ debugfs; TYPE_2__* bundle; struct gb_connection* connection; } ;
struct TYPE_8__ {scalar_t__ length; } ;
struct TYPE_6__ {int id; } ;
struct TYPE_5__ {int interface_id; } ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (struct gb_camera_debugfs_entry*) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GB_CAMERA_DEBUGFS_BUFFER_MAX ; 
 int /*<<< orphan*/  array_size (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  debugfs_create_dir (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debugfs_create_file (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct gb_camera*,int /*<<< orphan*/ *) ; 
 struct gb_camera_debugfs_entry* gb_camera_debugfs_entries ; 
 int /*<<< orphan*/  gb_camera_debugfs_ops ; 
 int /*<<< orphan*/  gb_debugfs_get () ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int,int) ; 
 TYPE_4__* vmalloc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int gb_camera_debugfs_init(struct gb_camera *gcam)
{
	struct gb_connection *connection = gcam->connection;
	char dirname[27];
	unsigned int i;

	/*
	 * Create root debugfs entry and a file entry for each camera operation.
	 */
	snprintf(dirname, 27, "camera-%u.%u", connection->intf->interface_id,
		 gcam->bundle->id);

	gcam->debugfs.root = debugfs_create_dir(dirname, gb_debugfs_get());

	gcam->debugfs.buffers =
		vmalloc(array_size(GB_CAMERA_DEBUGFS_BUFFER_MAX,
				   sizeof(*gcam->debugfs.buffers)));
	if (!gcam->debugfs.buffers)
		return -ENOMEM;

	for (i = 0; i < ARRAY_SIZE(gb_camera_debugfs_entries); ++i) {
		const struct gb_camera_debugfs_entry *entry =
			&gb_camera_debugfs_entries[i];

		gcam->debugfs.buffers[i].length = 0;

		debugfs_create_file(entry->name, entry->mask,
				    gcam->debugfs.root, gcam,
				    &gb_camera_debugfs_ops);
	}

	return 0;
}
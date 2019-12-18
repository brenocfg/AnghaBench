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
struct dentry {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* create_files ) (struct dentry*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  BUFFER_SIZE_DEFAULT ; 
 int /*<<< orphan*/  BUFFER_WATERSHED_DEFAULT ; 
 int /*<<< orphan*/  CPU_BUFFER_SIZE_DEFAULT ; 
 int /*<<< orphan*/  TIME_SLICE_DEFAULT ; 
 int /*<<< orphan*/  cpu_type_fops ; 
 int /*<<< orphan*/  depth_fops ; 
 int /*<<< orphan*/  dump_fops ; 
 int /*<<< orphan*/  enable_fops ; 
 int /*<<< orphan*/  event_buffer_fops ; 
 int /*<<< orphan*/  msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  oprofile_buffer_size ; 
 int /*<<< orphan*/  oprofile_buffer_watershed ; 
 int /*<<< orphan*/  oprofile_cpu_buffer_size ; 
 int /*<<< orphan*/  oprofile_create_stats_files (struct dentry*) ; 
 TYPE_1__ oprofile_ops ; 
 int /*<<< orphan*/  oprofile_time_slice ; 
 int /*<<< orphan*/  oprofilefs_create_file (struct dentry*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  oprofilefs_create_file_perm (struct dentry*,char*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  oprofilefs_create_ulong (struct dentry*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pointer_size_fops ; 
 int /*<<< orphan*/  stub1 (struct dentry*) ; 
 int /*<<< orphan*/  timeout_fops ; 

void oprofile_create_files(struct dentry *root)
{
	/* reinitialize default values */
	oprofile_buffer_size =		BUFFER_SIZE_DEFAULT;
	oprofile_cpu_buffer_size =	CPU_BUFFER_SIZE_DEFAULT;
	oprofile_buffer_watershed =	BUFFER_WATERSHED_DEFAULT;
	oprofile_time_slice =		msecs_to_jiffies(TIME_SLICE_DEFAULT);

	oprofilefs_create_file(root, "enable", &enable_fops);
	oprofilefs_create_file_perm(root, "dump", &dump_fops, 0666);
	oprofilefs_create_file(root, "buffer", &event_buffer_fops);
	oprofilefs_create_ulong(root, "buffer_size", &oprofile_buffer_size);
	oprofilefs_create_ulong(root, "buffer_watershed", &oprofile_buffer_watershed);
	oprofilefs_create_ulong(root, "cpu_buffer_size", &oprofile_cpu_buffer_size);
	oprofilefs_create_file(root, "cpu_type", &cpu_type_fops);
	oprofilefs_create_file(root, "backtrace_depth", &depth_fops);
	oprofilefs_create_file(root, "pointer_size", &pointer_size_fops);
#ifdef CONFIG_OPROFILE_EVENT_MULTIPLEX
	oprofilefs_create_file(root, "time_slice", &timeout_fops);
#endif
	oprofile_create_stats_files(root);
	if (oprofile_ops.create_files)
		oprofile_ops.create_files(root);
}
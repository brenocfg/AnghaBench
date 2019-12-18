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
struct dm_target_spec {int next; int /*<<< orphan*/  target_type; int /*<<< orphan*/  length; int /*<<< orphan*/  sector_start; scalar_t__ status; } ;
struct dm_target {TYPE_1__* type; int /*<<< orphan*/  len; int /*<<< orphan*/  begin; } ;
struct dm_table {int dummy; } ;
struct dm_ioctl {int flags; int data_start; size_t data_size; unsigned int target_count; } ;
typedef  int /*<<< orphan*/  status_type_t ;
struct TYPE_2__ {int /*<<< orphan*/  (* status ) (struct dm_target*,int /*<<< orphan*/ ,unsigned int,char*,size_t) ;int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int DM_BUFFER_FULL_FLAG ; 
 int DM_NOFLUSH_FLAG ; 
 unsigned int DM_STATUS_NOFLUSH_FLAG ; 
 int DM_STATUS_TABLE_FLAG ; 
 int /*<<< orphan*/  STATUSTYPE_INFO ; 
 int /*<<< orphan*/  STATUSTYPE_TABLE ; 
 char* align_ptr (char*) ; 
 unsigned int dm_table_get_num_targets (struct dm_table*) ; 
 struct dm_target* dm_table_get_target (struct dm_table*,unsigned int) ; 
 char* get_result_buffer (struct dm_ioctl*,size_t,size_t*) ; 
 int strlen (char*) ; 
 int /*<<< orphan*/  strncpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub1 (struct dm_target*,int /*<<< orphan*/ ,unsigned int,char*,size_t) ; 

__attribute__((used)) static void retrieve_status(struct dm_table *table,
			    struct dm_ioctl *param, size_t param_size)
{
	unsigned int i, num_targets;
	struct dm_target_spec *spec;
	char *outbuf, *outptr;
	status_type_t type;
	size_t remaining, len, used = 0;
	unsigned status_flags = 0;

	outptr = outbuf = get_result_buffer(param, param_size, &len);

	if (param->flags & DM_STATUS_TABLE_FLAG)
		type = STATUSTYPE_TABLE;
	else
		type = STATUSTYPE_INFO;

	/* Get all the target info */
	num_targets = dm_table_get_num_targets(table);
	for (i = 0; i < num_targets; i++) {
		struct dm_target *ti = dm_table_get_target(table, i);
		size_t l;

		remaining = len - (outptr - outbuf);
		if (remaining <= sizeof(struct dm_target_spec)) {
			param->flags |= DM_BUFFER_FULL_FLAG;
			break;
		}

		spec = (struct dm_target_spec *) outptr;

		spec->status = 0;
		spec->sector_start = ti->begin;
		spec->length = ti->len;
		strncpy(spec->target_type, ti->type->name,
			sizeof(spec->target_type));

		outptr += sizeof(struct dm_target_spec);
		remaining = len - (outptr - outbuf);
		if (remaining <= 0) {
			param->flags |= DM_BUFFER_FULL_FLAG;
			break;
		}

		/* Get the status/table string from the target driver */
		if (ti->type->status) {
			if (param->flags & DM_NOFLUSH_FLAG)
				status_flags |= DM_STATUS_NOFLUSH_FLAG;
			ti->type->status(ti, type, status_flags, outptr, remaining);
		} else
			outptr[0] = '\0';

		l = strlen(outptr) + 1;
		if (l == remaining) {
			param->flags |= DM_BUFFER_FULL_FLAG;
			break;
		}

		outptr += l;
		used = param->data_start + (outptr - outbuf);

		outptr = align_ptr(outptr);
		spec->next = outptr - outbuf;
	}

	if (used)
		param->data_size = used;

	param->target_count = num_targets;
}
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
struct dm_thin_new_mapping {int /*<<< orphan*/  status; } ;

/* Variables and functions */
 int /*<<< orphan*/  BLK_STS_IOERR ; 
 int /*<<< orphan*/  complete_mapping_preparation (struct dm_thin_new_mapping*) ; 

__attribute__((used)) static void copy_complete(int read_err, unsigned long write_err, void *context)
{
	struct dm_thin_new_mapping *m = context;

	m->status = read_err || write_err ? BLK_STS_IOERR : 0;
	complete_mapping_preparation(m);
}
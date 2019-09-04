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
struct mirror {int /*<<< orphan*/  error_type; int /*<<< orphan*/  error_count; } ;

/* Variables and functions */
 int /*<<< orphan*/  DM_RAID1_FLUSH_ERROR ; 
 int /*<<< orphan*/  DM_RAID1_READ_ERROR ; 
 int /*<<< orphan*/  DM_RAID1_SYNC_ERROR ; 
 int /*<<< orphan*/  DM_RAID1_WRITE_ERROR ; 
 int /*<<< orphan*/  atomic_read (int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static char device_status_char(struct mirror *m)
{
	if (!atomic_read(&(m->error_count)))
		return 'A';

	return (test_bit(DM_RAID1_FLUSH_ERROR, &(m->error_type))) ? 'F' :
		(test_bit(DM_RAID1_WRITE_ERROR, &(m->error_type))) ? 'D' :
		(test_bit(DM_RAID1_SYNC_ERROR, &(m->error_type))) ? 'S' :
		(test_bit(DM_RAID1_READ_ERROR, &(m->error_type))) ? 'R' : 'U';
}
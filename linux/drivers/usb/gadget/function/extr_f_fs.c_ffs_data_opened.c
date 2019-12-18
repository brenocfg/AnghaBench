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
struct ffs_data {scalar_t__ state; int /*<<< orphan*/  opened; int /*<<< orphan*/  ref; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENTER () ; 
 scalar_t__ FFS_CLOSING ; 
 scalar_t__ FFS_DEACTIVATED ; 
 int atomic_add_return (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ffs_data_reset (struct ffs_data*) ; 
 int /*<<< orphan*/  refcount_inc (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ffs_data_opened(struct ffs_data *ffs)
{
	ENTER();

	refcount_inc(&ffs->ref);
	if (atomic_add_return(1, &ffs->opened) == 1 &&
			ffs->state == FFS_DEACTIVATED) {
		ffs->state = FFS_CLOSING;
		ffs_data_reset(ffs);
	}
}
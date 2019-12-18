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
struct ffs_io_data {int /*<<< orphan*/  buf; int /*<<< orphan*/  sgt; scalar_t__ use_sg; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sg_free_table (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vfree (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void ffs_free_buffer(struct ffs_io_data *io_data)
{
	if (!io_data->buf)
		return;

	if (io_data->use_sg) {
		sg_free_table(&io_data->sgt);
		vfree(io_data->buf);
	} else {
		kfree(io_data->buf);
	}
}
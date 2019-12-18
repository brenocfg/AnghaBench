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
struct ffs_io_data {int /*<<< orphan*/  sgt; scalar_t__ use_sg; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 void* ffs_build_sg_list (int /*<<< orphan*/ *,size_t) ; 
 void* kmalloc (size_t,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void *ffs_alloc_buffer(struct ffs_io_data *io_data,
	size_t data_len)
{
	if (io_data->use_sg)
		return ffs_build_sg_list(&io_data->sgt, data_len);

	return kmalloc(data_len, GFP_KERNEL);
}
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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u64 ;
typedef  int u32 ;
struct esas2r_sg_context {scalar_t__ cur_offset; scalar_t__ adapter; } ;
struct esas2r_ioctl_fs {int dummy; } ;
struct esas2r_adapter {int ppfs_api_buffer; int fs_api_buffer_size; scalar_t__ fs_api_buffer; } ;

/* Variables and functions */

__attribute__((used)) static u32 get_physaddr_fs_api(struct esas2r_sg_context *sgc, u64 *addr)
{
	struct esas2r_adapter *a = (struct esas2r_adapter *)sgc->adapter;
	struct esas2r_ioctl_fs *fs =
		(struct esas2r_ioctl_fs *)a->fs_api_buffer;
	u32 offset = (u8 *)sgc->cur_offset - (u8 *)fs;

	(*addr) = a->ppfs_api_buffer + offset;

	return a->fs_api_buffer_size - offset;
}
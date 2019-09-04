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
struct drm_buf_map {TYPE_1__* list; } ;
struct drm_buf {unsigned long offset; unsigned long idx; unsigned long total; } ;
typedef  int /*<<< orphan*/  address ;
struct TYPE_2__ {int /*<<< orphan*/  address; int /*<<< orphan*/  used; int /*<<< orphan*/  total; int /*<<< orphan*/  idx; } ;

/* Variables and functions */
 int EFAULT ; 
 scalar_t__ clear_user (int /*<<< orphan*/ *,int) ; 
 scalar_t__ copy_to_user (int /*<<< orphan*/ *,unsigned long*,int) ; 

__attribute__((used)) static int map_one_buf(void *data, int idx, unsigned long virtual,
			struct drm_buf *buf)
{
	struct drm_buf_map *request = data;
	unsigned long address = virtual + buf->offset;	/* *** */

	if (copy_to_user(&request->list[idx].idx, &buf->idx,
			 sizeof(request->list[0].idx)))
		return -EFAULT;
	if (copy_to_user(&request->list[idx].total, &buf->total,
			 sizeof(request->list[0].total)))
		return -EFAULT;
	if (clear_user(&request->list[idx].used, sizeof(int)))
		return -EFAULT;
	if (copy_to_user(&request->list[idx].address, &address,
			 sizeof(address)))
		return -EFAULT;
	return 0;
}
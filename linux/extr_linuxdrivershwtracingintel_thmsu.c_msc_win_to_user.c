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
struct msc_win_to_user_struct {size_t buf; size_t offset; } ;

/* Variables and functions */
 unsigned long copy_to_user (size_t,void*,size_t) ; 

__attribute__((used)) static unsigned long msc_win_to_user(void *data, void *src, size_t len)
{
	struct msc_win_to_user_struct *u = data;
	unsigned long ret;

	ret = copy_to_user(u->buf + u->offset, src, len);
	u->offset += len - ret;

	return ret;
}
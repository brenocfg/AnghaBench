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
typedef  scalar_t__ u32 ;
typedef  scalar_t__ u16 ;
struct i40iw_puda_buf {scalar_t__ seqnum; scalar_t__ datalen; int /*<<< orphan*/  data; } ;

/* Variables and functions */

__attribute__((used)) static void i40iw_ieq_check_first_buf(struct i40iw_puda_buf *buf, u32 fps)
{
	u32 offset;

	if (buf->seqnum < fps) {
		offset = fps - buf->seqnum;
		if (offset > buf->datalen)
			return;
		buf->data += offset;
		buf->datalen -= (u16)offset;
		buf->seqnum = fps;
	}
}
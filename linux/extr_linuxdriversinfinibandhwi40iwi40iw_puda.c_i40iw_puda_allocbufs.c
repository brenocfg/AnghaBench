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
struct i40iw_puda_rsrc {scalar_t__ alloc_buf_count; scalar_t__ avail_buf_count; struct i40iw_puda_buf* alloclist; int /*<<< orphan*/  stats_buf_alloc_fail; int /*<<< orphan*/  buf_size; int /*<<< orphan*/  dev; } ;
struct i40iw_puda_buf {struct i40iw_puda_buf* next; } ;
typedef  enum i40iw_status_code { ____Placeholder_i40iw_status_code } i40iw_status_code ;

/* Variables and functions */
 int I40IW_ERR_NO_MEMORY ; 
 struct i40iw_puda_buf* i40iw_puda_alloc_buf (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i40iw_puda_ret_bufpool (struct i40iw_puda_rsrc*,struct i40iw_puda_buf*) ; 

__attribute__((used)) static enum i40iw_status_code i40iw_puda_allocbufs(struct i40iw_puda_rsrc *rsrc,
						   u32 count)
{
	u32 i;
	struct i40iw_puda_buf *buf;
	struct i40iw_puda_buf *nextbuf;

	for (i = 0; i < count; i++) {
		buf = i40iw_puda_alloc_buf(rsrc->dev, rsrc->buf_size);
		if (!buf) {
			rsrc->stats_buf_alloc_fail++;
			return I40IW_ERR_NO_MEMORY;
		}
		i40iw_puda_ret_bufpool(rsrc, buf);
		rsrc->alloc_buf_count++;
		if (!rsrc->alloclist) {
			rsrc->alloclist = buf;
		} else {
			nextbuf = rsrc->alloclist;
			rsrc->alloclist = buf;
			buf->next = nextbuf;
		}
	}
	rsrc->avail_buf_count = rsrc->alloc_buf_count;
	return 0;
}
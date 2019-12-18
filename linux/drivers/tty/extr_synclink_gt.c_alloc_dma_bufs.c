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
struct slgt_info {int rbuf_count; int tbuf_count; int /*<<< orphan*/  device_name; int /*<<< orphan*/  tbufs; int /*<<< orphan*/  rbufs; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBGERR (char*) ; 
 int ENOMEM ; 
 scalar_t__ alloc_bufs (struct slgt_info*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ alloc_desc (struct slgt_info*) ; 
 scalar_t__ alloc_tmp_rbuf (struct slgt_info*) ; 
 int /*<<< orphan*/  reset_rbufs (struct slgt_info*) ; 

__attribute__((used)) static int alloc_dma_bufs(struct slgt_info *info)
{
	info->rbuf_count = 32;
	info->tbuf_count = 32;

	if (alloc_desc(info) < 0 ||
	    alloc_bufs(info, info->rbufs, info->rbuf_count) < 0 ||
	    alloc_bufs(info, info->tbufs, info->tbuf_count) < 0 ||
	    alloc_tmp_rbuf(info) < 0) {
		DBGERR(("%s DMA buffer alloc fail\n", info->device_name));
		return -ENOMEM;
	}
	reset_rbufs(info);
	return 0;
}
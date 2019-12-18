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
struct slgt_info {int /*<<< orphan*/  tbuf_count; int /*<<< orphan*/  tbufs; int /*<<< orphan*/  rbuf_count; int /*<<< orphan*/  rbufs; scalar_t__ bufs; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_bufs (struct slgt_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_desc (struct slgt_info*) ; 
 int /*<<< orphan*/  free_tmp_rbuf (struct slgt_info*) ; 

__attribute__((used)) static void free_dma_bufs(struct slgt_info *info)
{
	if (info->bufs) {
		free_bufs(info, info->rbufs, info->rbuf_count);
		free_bufs(info, info->tbufs, info->tbuf_count);
		free_desc(info);
	}
	free_tmp_rbuf(info);
}
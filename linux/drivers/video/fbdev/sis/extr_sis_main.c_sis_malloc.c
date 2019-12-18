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
struct TYPE_2__ {struct sis_video_info* vinfo; } ;
struct sis_video_info {TYPE_1__ sisfb_heap; } ;
struct sis_memreq {scalar_t__ size; scalar_t__ offset; } ;

/* Variables and functions */
 int /*<<< orphan*/  sis_int_malloc (struct sis_video_info*,struct sis_memreq*) ; 
 TYPE_1__* sisfb_heap ; 

void
sis_malloc(struct sis_memreq *req)
{
	struct sis_video_info *ivideo = sisfb_heap->vinfo;

	if(&ivideo->sisfb_heap == sisfb_heap)
		sis_int_malloc(ivideo, req);
	else
		req->offset = req->size = 0;
}
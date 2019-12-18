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
struct nvkm_head_func {int dummy; } ;
struct nvkm_head {int id; int /*<<< orphan*/  head; struct nvkm_disp* disp; struct nvkm_head_func const* func; } ;
struct nvkm_disp {int /*<<< orphan*/  head; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  HEAD_DBG (struct nvkm_head*,char*) ; 
 struct nvkm_head* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int
nvkm_head_new_(const struct nvkm_head_func *func,
	       struct nvkm_disp *disp, int id)
{
	struct nvkm_head *head;
	if (!(head = kzalloc(sizeof(*head), GFP_KERNEL)))
		return -ENOMEM;
	head->func = func;
	head->disp = disp;
	head->id = id;
	list_add_tail(&head->head, &disp->head);
	HEAD_DBG(head, "ctor");
	return 0;
}
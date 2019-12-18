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
struct vhost_umem {int /*<<< orphan*/  umem_list; scalar_t__ numem; int /*<<< orphan*/  umem_tree; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RB_ROOT_CACHED ; 
 struct vhost_umem* kvzalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct vhost_umem *vhost_umem_alloc(void)
{
	struct vhost_umem *umem = kvzalloc(sizeof(*umem), GFP_KERNEL);

	if (!umem)
		return NULL;

	umem->umem_tree = RB_ROOT_CACHED;
	umem->numem = 0;
	INIT_LIST_HEAD(&umem->umem_list);

	return umem;
}
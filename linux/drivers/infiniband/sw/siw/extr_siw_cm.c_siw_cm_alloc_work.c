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
struct siw_cm_work {int /*<<< orphan*/  list; struct siw_cep* cep; } ;
struct siw_cep {int /*<<< orphan*/  work_freelist; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 struct siw_cm_work* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  siw_cm_free_work (struct siw_cep*) ; 

__attribute__((used)) static int siw_cm_alloc_work(struct siw_cep *cep, int num)
{
	struct siw_cm_work *work;

	while (num--) {
		work = kmalloc(sizeof(*work), GFP_KERNEL);
		if (!work) {
			if (!(list_empty(&cep->work_freelist)))
				siw_cm_free_work(cep);
			return -ENOMEM;
		}
		work->cep = cep;
		INIT_LIST_HEAD(&work->list);
		list_add(&work->list, &cep->work_freelist);
	}
	return 0;
}
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
struct sti_struct {int /*<<< orphan*/  lock; int /*<<< orphan*/  text_planes; int /*<<< orphan*/  glob_cfg; int /*<<< orphan*/  init_graph; TYPE_1__* sti_data; } ;
struct sti_init_outptr {int errno; int /*<<< orphan*/  text_planes; } ;
struct sti_init_inptr_ext {int text_planes; int /*<<< orphan*/  ext_ptr; } ;
struct sti_init_inptr {int text_planes; int /*<<< orphan*/  ext_ptr; } ;
struct TYPE_2__ {struct sti_init_outptr init_outptr; struct sti_init_inptr_ext init_inptr_ext; struct sti_init_inptr_ext init_inptr; } ;

/* Variables and functions */
 int /*<<< orphan*/  STI_PTR (struct sti_init_inptr_ext*) ; 
 int /*<<< orphan*/  default_init_flags ; 
 int /*<<< orphan*/  memset (struct sti_init_inptr_ext*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pr_err (char*,int,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int sti_call (struct sti_struct*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct sti_init_inptr_ext*,struct sti_init_outptr*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int sti_init_graph(struct sti_struct *sti)
{
	struct sti_init_inptr *inptr = &sti->sti_data->init_inptr;
	struct sti_init_inptr_ext *inptr_ext = &sti->sti_data->init_inptr_ext;
	struct sti_init_outptr *outptr = &sti->sti_data->init_outptr;
	unsigned long flags;
	int ret, err;

	spin_lock_irqsave(&sti->lock, flags);

	memset(inptr, 0, sizeof(*inptr));
	inptr->text_planes = 3; /* # of text planes (max 3 for STI) */
	memset(inptr_ext, 0, sizeof(*inptr_ext));
	inptr->ext_ptr = STI_PTR(inptr_ext);
	outptr->errno = 0;

	ret = sti_call(sti, sti->init_graph, &default_init_flags, inptr,
		outptr, sti->glob_cfg);

	if (ret >= 0)
		sti->text_planes = outptr->text_planes;
	err = outptr->errno;

	spin_unlock_irqrestore(&sti->lock, flags);

	if (ret < 0) {
		pr_err("STI init_graph failed (ret %d, errno %d)\n", ret, err);
		return -1;
	}
	
	return 0;
}
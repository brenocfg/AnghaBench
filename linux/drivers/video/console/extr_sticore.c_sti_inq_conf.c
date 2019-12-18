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
struct sti_struct {int /*<<< orphan*/  lock; int /*<<< orphan*/  glob_cfg; int /*<<< orphan*/  inq_conf; TYPE_1__* sti_data; } ;
struct sti_conf_outptr {int /*<<< orphan*/  ext_ptr; } ;
struct sti_conf_inptr {int dummy; } ;
typedef  int s32 ;
struct TYPE_2__ {int /*<<< orphan*/  inq_outptr_ext; struct sti_conf_outptr inq_outptr; struct sti_conf_inptr inq_inptr; } ;

/* Variables and functions */
 int /*<<< orphan*/  STI_PTR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  default_conf_flags ; 
 int /*<<< orphan*/  memset (struct sti_conf_inptr*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int sti_call (struct sti_struct*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct sti_conf_inptr*,struct sti_conf_outptr*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void sti_inq_conf(struct sti_struct *sti)
{
	struct sti_conf_inptr *inptr = &sti->sti_data->inq_inptr;
	struct sti_conf_outptr *outptr = &sti->sti_data->inq_outptr;
	unsigned long flags;
	s32 ret;

	outptr->ext_ptr = STI_PTR(&sti->sti_data->inq_outptr_ext);
	
	do {
		spin_lock_irqsave(&sti->lock, flags);
		memset(inptr, 0, sizeof(*inptr));
		ret = sti_call(sti, sti->inq_conf, &default_conf_flags,
			inptr, outptr, sti->glob_cfg);
		spin_unlock_irqrestore(&sti->lock, flags);
	} while (ret == 1);
}
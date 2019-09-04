#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int execute_only_pkey; } ;
struct mm_struct {TYPE_1__ context; } ;
struct TYPE_8__ {scalar_t__ initialized; } ;
struct TYPE_7__ {TYPE_3__ fpu; } ;
struct TYPE_9__ {TYPE_2__ thread; } ;

/* Variables and functions */
 int /*<<< orphan*/  PKEY_DISABLE_ACCESS ; 
 int /*<<< orphan*/  __pkru_allows_read (int /*<<< orphan*/ ,int) ; 
 int arch_set_user_pkey_access (TYPE_4__*,int,int /*<<< orphan*/ ) ; 
 TYPE_4__* current ; 
 int mm_pkey_alloc (struct mm_struct*) ; 
 int /*<<< orphan*/  mm_set_pkey_free (struct mm_struct*,int) ; 
 int /*<<< orphan*/  preempt_disable () ; 
 int /*<<< orphan*/  preempt_enable () ; 
 int /*<<< orphan*/  read_pkru () ; 

int __execute_only_pkey(struct mm_struct *mm)
{
	bool need_to_set_mm_pkey = false;
	int execute_only_pkey = mm->context.execute_only_pkey;
	int ret;

	/* Do we need to assign a pkey for mm's execute-only maps? */
	if (execute_only_pkey == -1) {
		/* Go allocate one to use, which might fail */
		execute_only_pkey = mm_pkey_alloc(mm);
		if (execute_only_pkey < 0)
			return -1;
		need_to_set_mm_pkey = true;
	}

	/*
	 * We do not want to go through the relatively costly
	 * dance to set PKRU if we do not need to.  Check it
	 * first and assume that if the execute-only pkey is
	 * write-disabled that we do not have to set it
	 * ourselves.  We need preempt off so that nobody
	 * can make fpregs inactive.
	 */
	preempt_disable();
	if (!need_to_set_mm_pkey &&
	    current->thread.fpu.initialized &&
	    !__pkru_allows_read(read_pkru(), execute_only_pkey)) {
		preempt_enable();
		return execute_only_pkey;
	}
	preempt_enable();

	/*
	 * Set up PKRU so that it denies access for everything
	 * other than execution.
	 */
	ret = arch_set_user_pkey_access(current, execute_only_pkey,
			PKEY_DISABLE_ACCESS);
	/*
	 * If the PKRU-set operation failed somehow, just return
	 * 0 and effectively disable execute-only support.
	 */
	if (ret) {
		mm_set_pkey_free(mm, execute_only_pkey);
		return -1;
	}

	/* We got one, store it and use it from here on out */
	if (need_to_set_mm_pkey)
		mm->context.execute_only_pkey = execute_only_pkey;
	return execute_only_pkey;
}
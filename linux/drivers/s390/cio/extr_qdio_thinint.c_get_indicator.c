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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_2__ {int /*<<< orphan*/  ind; int /*<<< orphan*/  count; } ;

/* Variables and functions */
 int TIQDIO_NR_NONSHARED_IND ; 
 size_t TIQDIO_SHARED_IND ; 
 int /*<<< orphan*/  atomic_cmpxchg (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 TYPE_1__* q_indicators ; 

__attribute__((used)) static u32 *get_indicator(void)
{
	int i;

	for (i = 0; i < TIQDIO_NR_NONSHARED_IND; i++)
		if (!atomic_cmpxchg(&q_indicators[i].count, 0, 1))
			return &q_indicators[i].ind;

	/* use the shared indicator */
	atomic_inc(&q_indicators[TIQDIO_SHARED_IND].count);
	return &q_indicators[TIQDIO_SHARED_IND].ind;
}
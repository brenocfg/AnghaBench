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
struct hmm_range {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  hmm_range_unregister (struct hmm_range*) ; 
 int hmm_range_valid (struct hmm_range*) ; 

__attribute__((used)) static inline bool
nouveau_range_done(struct hmm_range *range)
{
	bool ret = hmm_range_valid(range);

	hmm_range_unregister(range);
	return ret;
}
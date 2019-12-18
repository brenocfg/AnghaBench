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
typedef  int /*<<< orphan*/  u32 ;
struct ccw1 {int /*<<< orphan*/  cda; } ;

/* Variables and functions */
 int /*<<< orphan*/  ccw_is_tic (struct ccw1*) ; 
 int is_cpa_within_range (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline int is_tic_within_range(struct ccw1 *ccw, u32 head, int len)
{
	if (!ccw_is_tic(ccw))
		return 0;

	return is_cpa_within_range(ccw->cda, head, len);
}
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
struct TYPE_2__ {int /*<<< orphan*/  compcode; } ;
union zip_zres_s {TYPE_1__ s; } ;

/* Variables and functions */
 int ETIMEDOUT ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  rmb () ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static inline int zip_poll_result(union zip_zres_s *result)
{
	int retries = 1000;

	while (!result->s.compcode) {
		if (!--retries) {
			pr_err("ZIP ERR: request timed out");
			return -ETIMEDOUT;
		}
		udelay(10);
		/*
		 * Force re-reading of compcode which is updated
		 * by the ZIP coprocessor.
		 */
		rmb();
	}
	return 0;
}
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
struct ar9170 {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  modparam_noht ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline unsigned int __carl9170_get_queue(struct ar9170 *ar,
						unsigned int queue)
{
	if (unlikely(modparam_noht)) {
		return queue;
	} else {
		/*
		 * This is just another workaround, until
		 * someone figures out how to get QoS and
		 * AMPDU to play nicely together.
		 */

		return 2;		/* AC_BE */
	}
}
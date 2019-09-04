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
struct multipath {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 unsigned long READ_ONCE (int /*<<< orphan*/ ) ; 
 int __must_push_back (struct multipath*,unsigned long) ; 

__attribute__((used)) static bool must_push_back_bio(struct multipath *m)
{
	unsigned long flags = READ_ONCE(m->flags);
	return __must_push_back(m, flags);
}
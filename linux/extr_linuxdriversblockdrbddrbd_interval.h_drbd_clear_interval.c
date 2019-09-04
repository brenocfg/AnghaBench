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
struct drbd_interval {int /*<<< orphan*/  rb; } ;

/* Variables and functions */
 int /*<<< orphan*/  RB_CLEAR_NODE (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void drbd_clear_interval(struct drbd_interval *i)
{
	RB_CLEAR_NODE(&i->rb);
}
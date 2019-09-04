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
struct module {int dummy; } ;

/* Variables and functions */
 scalar_t__ in_core (struct module*,void*) ; 
 scalar_t__ in_init (struct module*,void*) ; 

__attribute__((used)) static inline int in_local(struct module *me, void *loc)
{
	return in_init(me, loc) || in_core(me, loc);
}
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
struct string {unsigned long size; } ;
struct list_head {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_string (struct list_head*,struct string*) ; 

__attribute__((used)) static inline void
add_string_memory(struct list_head *free_list, void *mem, unsigned long size)
{
	struct string *cs;

	cs = (struct string *) mem;
	cs->size = size - sizeof(struct string);
	free_string(free_list, cs);
}
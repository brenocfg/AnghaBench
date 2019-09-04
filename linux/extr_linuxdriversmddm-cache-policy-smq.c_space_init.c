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
struct entry_space {int /*<<< orphan*/ * begin; int /*<<< orphan*/ * end; } ;
struct entry {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  array_size (unsigned int,int) ; 
 int /*<<< orphan*/ * vzalloc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int space_init(struct entry_space *es, unsigned nr_entries)
{
	if (!nr_entries) {
		es->begin = es->end = NULL;
		return 0;
	}

	es->begin = vzalloc(array_size(nr_entries, sizeof(struct entry)));
	if (!es->begin)
		return -ENOMEM;

	es->end = es->begin + nr_entries;
	return 0;
}
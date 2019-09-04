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
struct device {int dummy; } ;
struct component_match_array {int /*<<< orphan*/  data; int /*<<< orphan*/  (* release ) (struct device*,int /*<<< orphan*/ ) ;} ;
struct component_match {unsigned int num; struct component_match_array* compare; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct component_match_array*) ; 
 int /*<<< orphan*/  stub1 (struct device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void component_match_release(struct device *master,
	struct component_match *match)
{
	unsigned int i;

	for (i = 0; i < match->num; i++) {
		struct component_match_array *mc = &match->compare[i];

		if (mc->release)
			mc->release(master, mc->data);
	}

	kfree(match->compare);
}
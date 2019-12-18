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
struct selector {int dummy; } ;
struct path_selector {struct selector* context; } ;

/* Variables and functions */
 int ENOMEM ; 
 struct selector* alloc_selector () ; 

__attribute__((used)) static int rr_create(struct path_selector *ps, unsigned argc, char **argv)
{
	struct selector *s;

	s = alloc_selector();
	if (!s)
		return -ENOMEM;

	ps->context = s;
	return 0;
}
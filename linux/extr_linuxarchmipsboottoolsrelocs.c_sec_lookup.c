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
struct section {int dummy; } ;
struct TYPE_2__ {int e_shnum; } ;

/* Variables and functions */
 TYPE_1__ ehdr ; 
 int /*<<< orphan*/  sec_name (int) ; 
 struct section* secs ; 
 scalar_t__ strcmp (char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct section *sec_lookup(const char *secname)
{
	int i;

	for (i = 0; i < ehdr.e_shnum; i++)
		if (strcmp(secname, sec_name(i)) == 0)
			return &secs[i];

	return NULL;
}
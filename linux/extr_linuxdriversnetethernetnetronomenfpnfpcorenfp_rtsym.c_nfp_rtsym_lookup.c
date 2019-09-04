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
struct nfp_rtsym_table {int num; struct nfp_rtsym const* symtab; } ;
struct nfp_rtsym {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 scalar_t__ strcmp (char const*,int /*<<< orphan*/ ) ; 

const struct nfp_rtsym *
nfp_rtsym_lookup(struct nfp_rtsym_table *rtbl, const char *name)
{
	int n;

	if (!rtbl)
		return NULL;

	for (n = 0; n < rtbl->num; n++)
		if (strcmp(name, rtbl->symtab[n].name) == 0)
			return &rtbl->symtab[n];

	return NULL;
}
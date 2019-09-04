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
struct clk_bulk_data {struct clk* clk; int /*<<< orphan*/  id; } ;
struct clk {int dummy; } ;
typedef  int /*<<< orphan*/  n ;

/* Variables and functions */
 int /*<<< orphan*/  snprintf (char*,int,char*,char const*) ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char const*) ; 

struct clk *msm_clk_bulk_get_clock(struct clk_bulk_data *bulk, int count,
		const char *name)
{
	int i;
	char n[32];

	snprintf(n, sizeof(n), "%s_clk", name);

	for (i = 0; bulk && i < count; i++) {
		if (!strcmp(bulk[i].id, name) || !strcmp(bulk[i].id, n))
			return bulk[i].clk;
	}


	return NULL;
}
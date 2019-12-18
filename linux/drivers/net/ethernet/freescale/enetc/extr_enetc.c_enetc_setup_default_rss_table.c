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
struct enetc_si {int num_rss; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  enetc_set_rss_table (struct enetc_si*,int*,int) ; 
 int /*<<< orphan*/  kfree (int*) ; 
 int* kmalloc_array (int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int enetc_setup_default_rss_table(struct enetc_si *si, int num_groups)
{
	int *rss_table;
	int i;

	rss_table = kmalloc_array(si->num_rss, sizeof(*rss_table), GFP_KERNEL);
	if (!rss_table)
		return -ENOMEM;

	/* Set up RSS table defaults */
	for (i = 0; i < si->num_rss; i++)
		rss_table[i] = i % num_groups;

	enetc_set_rss_table(si, rss_table, si->num_rss);

	kfree(rss_table);

	return 0;
}
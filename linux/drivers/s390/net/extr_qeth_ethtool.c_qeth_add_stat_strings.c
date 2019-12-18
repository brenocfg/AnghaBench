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
typedef  int /*<<< orphan*/  u8 ;
struct qeth_stats {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_GSTRING_LEN ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void qeth_add_stat_strings(u8 **data, const char *prefix,
				  const struct qeth_stats stats[],
				  unsigned int size)
{
	unsigned int i;

	for (i = 0; i < size; i++) {
		snprintf(*data, ETH_GSTRING_LEN, "%s%s", prefix, stats[i].name);
		*data += ETH_GSTRING_LEN;
	}
}
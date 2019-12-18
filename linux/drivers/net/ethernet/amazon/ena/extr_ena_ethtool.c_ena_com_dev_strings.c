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
struct ena_stats {char* name; } ;

/* Variables and functions */
 int ENA_STATS_ARRAY_ENA_COM ; 
 int /*<<< orphan*/  ETH_GSTRING_LEN ; 
 struct ena_stats* ena_stats_ena_com_strings ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,char*) ; 

__attribute__((used)) static void ena_com_dev_strings(u8 **data)
{
	const struct ena_stats *ena_stats;
	int i;

	for (i = 0; i < ENA_STATS_ARRAY_ENA_COM; i++) {
		ena_stats = &ena_stats_ena_com_strings[i];

		snprintf(*data, ETH_GSTRING_LEN,
			 "ena_admin_q_%s", ena_stats->name);
		(*data) += ETH_GSTRING_LEN;
	}
}
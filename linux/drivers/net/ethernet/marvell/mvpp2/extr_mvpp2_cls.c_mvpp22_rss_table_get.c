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
struct mvpp2_rss_table {int dummy; } ;
struct mvpp2 {struct mvpp2_rss_table** rss_tables; } ;

/* Variables and functions */
 int MVPP22_N_RSS_TABLES ; 

__attribute__((used)) static struct mvpp2_rss_table *mvpp22_rss_table_get(struct mvpp2 *priv,
						    int rss_ctx)
{
	if (rss_ctx < 0 || rss_ctx >= MVPP22_N_RSS_TABLES)
		return NULL;

	return priv->rss_tables[rss_ctx];
}
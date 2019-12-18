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
struct cache_stats {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  cache_hits; } ;
struct cache_accounting {TYPE_1__ total; } ;

/* Variables and functions */
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

void bch_cache_accounting_clear(struct cache_accounting *acc)
{
	memset(&acc->total.cache_hits,
	       0,
	       sizeof(struct cache_stats));
}
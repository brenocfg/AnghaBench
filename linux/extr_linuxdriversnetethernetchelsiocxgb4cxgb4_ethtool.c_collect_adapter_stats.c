#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  void* u64 ;
struct adapter_stats {void* wc_fail; void* wc_success; int /*<<< orphan*/  db_empty; int /*<<< orphan*/  db_full; int /*<<< orphan*/  db_drop; } ;
struct TYPE_4__ {int /*<<< orphan*/  chip; } ;
struct TYPE_3__ {int /*<<< orphan*/  db_empty; int /*<<< orphan*/  db_full; int /*<<< orphan*/  db_drop; } ;
struct adapter {TYPE_2__ params; TYPE_1__ db_stats; } ;

/* Variables and functions */
 int /*<<< orphan*/  SGE_STAT_CFG_A ; 
 int /*<<< orphan*/  SGE_STAT_MATCH_A ; 
 int /*<<< orphan*/  SGE_STAT_TOTAL_A ; 
 int STATSOURCE_T5_G (int) ; 
 int /*<<< orphan*/  is_t4 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct adapter_stats*,int /*<<< orphan*/ ,int) ; 
 void* t4_read_reg (struct adapter*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void collect_adapter_stats(struct adapter *adap, struct adapter_stats *s)
{
	u64 val1, val2;

	memset(s, 0, sizeof(*s));

	s->db_drop = adap->db_stats.db_drop;
	s->db_full = adap->db_stats.db_full;
	s->db_empty = adap->db_stats.db_empty;

	if (!is_t4(adap->params.chip)) {
		int v;

		v = t4_read_reg(adap, SGE_STAT_CFG_A);
		if (STATSOURCE_T5_G(v) == 7) {
			val2 = t4_read_reg(adap, SGE_STAT_MATCH_A);
			val1 = t4_read_reg(adap, SGE_STAT_TOTAL_A);
			s->wc_success = val1 - val2;
			s->wc_fail = val2;
		}
	}
}
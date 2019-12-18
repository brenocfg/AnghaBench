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
typedef  int u8 ;
typedef  int u16 ;
struct adapter {scalar_t__* port; } ;
struct TYPE_2__ {unsigned int nqsets; } ;

/* Variables and functions */
 int F_HASHTOEPLITZ ; 
 int F_RQFEEDBACKENABLE ; 
 int F_TNL2TUPEN ; 
 int F_TNL4TUPEN ; 
 int F_TNLLKPEN ; 
 int F_TNLMAPEN ; 
 int F_TNLPRTEN ; 
 int RSS_TABLE_SIZE ; 
 int SGE_QSETS ; 
 int V_RRCPLCPUSIZE (int) ; 
 TYPE_1__* adap2pinfo (struct adapter*,int) ; 
 int /*<<< orphan*/  t3_config_rss (struct adapter*,int,int*,int*) ; 

__attribute__((used)) static void setup_rss(struct adapter *adap)
{
	int i;
	unsigned int nq0 = adap2pinfo(adap, 0)->nqsets;
	unsigned int nq1 = adap->port[1] ? adap2pinfo(adap, 1)->nqsets : 1;
	u8 cpus[SGE_QSETS + 1];
	u16 rspq_map[RSS_TABLE_SIZE + 1];

	for (i = 0; i < SGE_QSETS; ++i)
		cpus[i] = i;
	cpus[SGE_QSETS] = 0xff;	/* terminator */

	for (i = 0; i < RSS_TABLE_SIZE / 2; ++i) {
		rspq_map[i] = i % nq0;
		rspq_map[i + RSS_TABLE_SIZE / 2] = (i % nq1) + nq0;
	}
	rspq_map[RSS_TABLE_SIZE] = 0xffff; /* terminator */

	t3_config_rss(adap, F_RQFEEDBACKENABLE | F_TNLLKPEN | F_TNLMAPEN |
		      F_TNLPRTEN | F_TNL2TUPEN | F_TNL4TUPEN |
		      V_RRCPLCPUSIZE(6) | F_HASHTOEPLITZ, cpus, rspq_map);
}
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
struct TYPE_2__ {int /*<<< orphan*/  chip; } ;
struct adapter {TYPE_1__ params; } ;

/* Variables and functions */
 scalar_t__ CHELSIO_CHIP_VERSION (int /*<<< orphan*/ ) ; 
 scalar_t__ CHELSIO_T5 ; 
 unsigned int RSS_NENTRIES ; 
 unsigned int T6_RSS_NENTRIES ; 

unsigned int t4_chip_rss_size(struct adapter *adap)
{
	if (CHELSIO_CHIP_VERSION(adap->params.chip) <= CHELSIO_T5)
		return RSS_NENTRIES;
	else
		return T6_RSS_NENTRIES;
}
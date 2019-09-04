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
struct adapter {int dummy; } ;

/* Variables and functions */
 int sge_qinfo_uld_rspq_entries (struct adapter const*,int,int) ; 

__attribute__((used)) static int sge_qinfo_uld_rxq_entries(const struct adapter *adap, int uld)
{
	return sge_qinfo_uld_rspq_entries(adap, uld, false);
}
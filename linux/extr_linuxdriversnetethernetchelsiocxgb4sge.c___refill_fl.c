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
struct sge_fl {scalar_t__ avail; } ;
struct adapter {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  MAX_RX_REFILL ; 
 scalar_t__ fl_cap (struct sge_fl*) ; 
 int /*<<< orphan*/  min (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  refill_fl (struct adapter*,struct sge_fl*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void __refill_fl(struct adapter *adap, struct sge_fl *fl)
{
	refill_fl(adap, fl, min(MAX_RX_REFILL, fl_cap(fl) - fl->avail),
		  GFP_ATOMIC);
}
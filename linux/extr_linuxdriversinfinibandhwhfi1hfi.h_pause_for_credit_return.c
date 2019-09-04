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
typedef  int u32 ;
struct hfi1_devdata {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PACKET_EGRESS_TIMEOUT ; 
 int cclock_to_ns (struct hfi1_devdata*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static inline void pause_for_credit_return(struct hfi1_devdata *dd)
{
	/* Pause at least 1us, to ensure chip returns all credits */
	u32 usec = cclock_to_ns(dd, PACKET_EGRESS_TIMEOUT) / 1000;

	udelay(usec ? usec : 1);
}
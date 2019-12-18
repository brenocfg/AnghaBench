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
struct filter_entry {int dummy; } ;
struct adapter {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  TCB_T_FLAGS_W ; 
 int set_tcb_field (struct adapter*,struct filter_entry*,unsigned int,int /*<<< orphan*/ ,unsigned long long,unsigned long long,int) ; 

__attribute__((used)) static int set_tcb_tflag(struct adapter *adap, struct filter_entry *f,
			 unsigned int ftid, unsigned int bit_pos,
			 unsigned int val, int no_reply)
{
	return set_tcb_field(adap, f, ftid,  TCB_T_FLAGS_W, 1ULL << bit_pos,
			     (unsigned long long)val << bit_pos, no_reply);
}
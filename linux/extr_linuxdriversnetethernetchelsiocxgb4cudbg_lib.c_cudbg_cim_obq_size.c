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
struct adapter {int dummy; } ;

/* Variables and functions */
 int CIMQSIZE_G (int) ; 
 int /*<<< orphan*/  CIM_QUEUE_CONFIG_CTRL_A ; 
 int /*<<< orphan*/  CIM_QUEUE_CONFIG_REF_A ; 
 int OBQSELECT_F ; 
 int QUENUMSELECT_V (int) ; 
 int t4_read_reg (struct adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  t4_write_reg (struct adapter*,int /*<<< orphan*/ ,int) ; 

u32 cudbg_cim_obq_size(struct adapter *padap, int qid)
{
	u32 value;

	t4_write_reg(padap, CIM_QUEUE_CONFIG_REF_A, OBQSELECT_F |
		     QUENUMSELECT_V(qid));
	value = t4_read_reg(padap, CIM_QUEUE_CONFIG_CTRL_A);
	value = CIMQSIZE_G(value) * 64; /* size in number of words */
	return value * sizeof(u32);
}
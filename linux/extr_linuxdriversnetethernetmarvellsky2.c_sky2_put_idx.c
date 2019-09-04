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
typedef  int /*<<< orphan*/  u16 ;
struct sky2_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PREF_UNIT_PUT_IDX ; 
 int /*<<< orphan*/  Y2_QADDR (unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmiowb () ; 
 int /*<<< orphan*/  sky2_write16 (struct sky2_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wmb () ; 

__attribute__((used)) static inline void sky2_put_idx(struct sky2_hw *hw, unsigned q, u16 idx)
{
	/* Make sure write' to descriptors are complete before we tell hardware */
	wmb();
	sky2_write16(hw, Y2_QADDR(q, PREF_UNIT_PUT_IDX), idx);

	/* Synchronize I/O on since next processor may write to tail */
	mmiowb();
}
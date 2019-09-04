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
typedef  int /*<<< orphan*/  u32 ;
struct mpic {int /*<<< orphan*/  tmregs; int /*<<< orphan*/  reg_type; } ;

/* Variables and functions */
 unsigned int MPIC_INFO (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TIMER_VECTOR_PRI ; 
 int /*<<< orphan*/  _mpic_read (int /*<<< orphan*/ ,int /*<<< orphan*/ *,unsigned int) ; 
 unsigned int mpic_tm_offset (struct mpic*,unsigned int) ; 

__attribute__((used)) static inline u32 _mpic_tm_read(struct mpic *mpic, unsigned int tm)
{
	unsigned int offset = mpic_tm_offset(mpic, tm) +
			      MPIC_INFO(TIMER_VECTOR_PRI);

	return _mpic_read(mpic->reg_type, &mpic->tmregs, offset);
}
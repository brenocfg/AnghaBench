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
struct tg3 {int /*<<< orphan*/  (* read32_mbox ) (struct tg3*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* write32_mbox ) (struct tg3*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  FLUSH_POSTED_WRITES ; 
 int /*<<< orphan*/  ICH_WORKAROUND ; 
 int /*<<< orphan*/  MBOX_WRITE_REORDER ; 
 int /*<<< orphan*/  stub1 (struct tg3*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (struct tg3*,int /*<<< orphan*/ ) ; 
 scalar_t__ tg3_flag (struct tg3*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void tw32_mailbox_flush(struct tg3 *tp, u32 off, u32 val)
{
	tp->write32_mbox(tp, off, val);
	if (tg3_flag(tp, FLUSH_POSTED_WRITES) ||
	    (!tg3_flag(tp, MBOX_WRITE_REORDER) &&
	     !tg3_flag(tp, ICH_WORKAROUND)))
		tp->read32_mbox(tp, off);
}
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
typedef  int /*<<< orphan*/  u64 ;
typedef  scalar_t__ u32 ;
struct i40iw_sge {int /*<<< orphan*/  stag; int /*<<< orphan*/  len; int /*<<< orphan*/  tag_off; } ;

/* Variables and functions */
 int /*<<< orphan*/  I40IWQPSQ_FRAG_LEN ; 
 int /*<<< orphan*/  I40IWQPSQ_FRAG_STAG ; 
 int /*<<< orphan*/  I40IWQPSQ_FRAG_TO ; 
 int LS_64 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_64bit_val (int /*<<< orphan*/ *,scalar_t__,int) ; 

__attribute__((used)) static void i40iw_set_fragment(u64 *wqe, u32 offset, struct i40iw_sge *sge)
{
	if (sge) {
		set_64bit_val(wqe, offset, LS_64(sge->tag_off, I40IWQPSQ_FRAG_TO));
		set_64bit_val(wqe, (offset + 8),
			      (LS_64(sge->len, I40IWQPSQ_FRAG_LEN) |
			       LS_64(sge->stag, I40IWQPSQ_FRAG_STAG)));
	}
}
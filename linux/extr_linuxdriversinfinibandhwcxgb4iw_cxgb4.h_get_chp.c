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
struct c4iw_dev {int /*<<< orphan*/  cqidr; } ;
struct c4iw_cq {int dummy; } ;

/* Variables and functions */
 struct c4iw_cq* idr_find (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline struct c4iw_cq *get_chp(struct c4iw_dev *rhp, u32 cqid)
{
	return idr_find(&rhp->cqidr, cqid);
}
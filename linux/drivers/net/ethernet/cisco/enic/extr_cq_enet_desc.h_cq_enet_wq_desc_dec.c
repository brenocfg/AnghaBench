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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct cq_enet_wq_desc {int dummy; } ;
struct cq_desc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  cq_desc_dec (struct cq_desc*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void cq_enet_wq_desc_dec(struct cq_enet_wq_desc *desc,
	u8 *type, u8 *color, u16 *q_number, u16 *completed_index)
{
	cq_desc_dec((struct cq_desc *)desc, type,
		color, q_number, completed_index);
}
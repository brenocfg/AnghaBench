#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u16 ;
struct TYPE_2__ {int size; } ;
struct t4_wq {TYPE_1__ sq; } ;

/* Variables and functions */
 int T4_SQ_NUM_SLOTS ; 

__attribute__((used)) static inline u16 t4_sq_wq_size(struct t4_wq *wq)
{
		return wq->sq.size * T4_SQ_NUM_SLOTS;
}
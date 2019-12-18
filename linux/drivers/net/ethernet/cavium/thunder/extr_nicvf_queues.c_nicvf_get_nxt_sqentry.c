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
struct TYPE_2__ {int q_len; } ;
struct snd_queue {TYPE_1__ dmem; } ;

/* Variables and functions */

__attribute__((used)) static inline int nicvf_get_nxt_sqentry(struct snd_queue *sq, int qentry)
{
	qentry++;
	qentry &= (sq->dmem.q_len - 1);
	return qentry;
}
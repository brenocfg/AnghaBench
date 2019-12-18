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
struct rs_rate {scalar_t__ ant; scalar_t__ type; scalar_t__ bw; scalar_t__ sgi; scalar_t__ bfer; scalar_t__ stbc; } ;

/* Variables and functions */
 scalar_t__ ANT_A ; 
 scalar_t__ ANT_B ; 

__attribute__((used)) static inline bool rs_rate_column_match(struct rs_rate *a,
					struct rs_rate *b)
{
	bool ant_match;

	if (a->stbc || a->bfer)
		ant_match = (b->ant == ANT_A || b->ant == ANT_B);
	else
		ant_match = (a->ant == b->ant);

	return (a->type == b->type) && (a->bw == b->bw) && (a->sgi == b->sgi)
		&& ant_match;
}
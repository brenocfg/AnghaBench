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
struct stats {int hits; scalar_t__ misses; } ;
typedef  enum performance { ____Placeholder_performance } performance ;

/* Variables and functions */
 unsigned int EIGHTH ; 
 int FP_SHIFT ; 
 int Q_FAIR ; 
 int Q_POOR ; 
 int Q_WELL ; 
 unsigned int SIXTEENTH ; 
 unsigned int safe_div (int,scalar_t__) ; 

__attribute__((used)) static enum performance stats_assess(struct stats *s)
{
	unsigned confidence = safe_div(s->hits << FP_SHIFT, s->hits + s->misses);

	if (confidence < SIXTEENTH)
		return Q_POOR;

	else if (confidence < EIGHTH)
		return Q_FAIR;

	else
		return Q_WELL;
}
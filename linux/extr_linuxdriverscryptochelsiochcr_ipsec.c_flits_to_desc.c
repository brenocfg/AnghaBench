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

/* Variables and functions */
 unsigned int DIV_ROUND_UP (unsigned int,int) ; 
 int SGE_MAX_WR_LEN ; 
 int /*<<< orphan*/  WARN_ON (int) ; 

__attribute__((used)) static inline unsigned int flits_to_desc(unsigned int n)
{
	WARN_ON(n > SGE_MAX_WR_LEN / 8);
	return DIV_ROUND_UP(n, 8);
}
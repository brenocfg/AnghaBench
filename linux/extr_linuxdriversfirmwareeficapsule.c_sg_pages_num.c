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
 unsigned int DIV_ROUND_UP (unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SGLIST_PER_PAGE ; 

__attribute__((used)) static inline unsigned int sg_pages_num(unsigned int count)
{
	return DIV_ROUND_UP(count, SGLIST_PER_PAGE);
}
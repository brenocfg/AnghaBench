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
typedef  int /*<<< orphan*/  x ;
typedef  unsigned int u16 ;

/* Variables and functions */
 int /*<<< orphan*/  get_random_bytes (unsigned int*,int) ; 

__attribute__((used)) static unsigned int
random_ri(void)
{
	u16 x;

	get_random_bytes(&x, sizeof(x));
	return x;
}
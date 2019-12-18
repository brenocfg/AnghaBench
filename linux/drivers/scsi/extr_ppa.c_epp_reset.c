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
 int r_str (unsigned short) ; 
 int /*<<< orphan*/  w_str (unsigned short,int) ; 

__attribute__((used)) static inline void epp_reset(unsigned short ppb)
{
	int i;

	i = r_str(ppb);
	w_str(ppb, i);
	w_str(ppb, i & 0xfe);
}
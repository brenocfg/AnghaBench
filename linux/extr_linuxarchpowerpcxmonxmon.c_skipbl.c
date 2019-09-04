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
 int inchar () ; 
 int termch ; 

int
skipbl(void)
{
	int c;

	if( termch != 0 ){
		c = termch;
		termch = 0;
	} else
		c = inchar();
	while( c == ' ' || c == '\t' )
		c = inchar();
	return c;
}
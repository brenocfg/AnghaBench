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
typedef  int /*<<< orphan*/  PIA ;

/* Variables and functions */
 int /*<<< orphan*/  CMD (int) ; 
 int* cont_map ; 
 int j44 (int,int) ; 
 int r1 () ; 
 int /*<<< orphan*/  w2 (int) ; 

__attribute__((used)) static int friq_read_regr( PIA *pi, int cont, int regr )

{	int	h,l,r;

	r = regr + cont_map[cont];

	CMD(r);
	w2(6); l = r1();
	w2(4); h = r1();
	w2(4); 

	return j44(l,h);

}
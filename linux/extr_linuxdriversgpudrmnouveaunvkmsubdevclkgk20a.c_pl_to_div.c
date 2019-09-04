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
typedef  int u32 ;

/* Variables and functions */
 int ARRAY_SIZE (int*) ; 
 int* _pl_to_div ; 

__attribute__((used)) static u32 pl_to_div(u32 pl)
{
	if (pl >= ARRAY_SIZE(_pl_to_div))
		return 1;

	return _pl_to_div[pl];
}
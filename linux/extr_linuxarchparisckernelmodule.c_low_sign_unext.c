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
 int sign_unext (int,int) ; 

__attribute__((used)) static inline int low_sign_unext(int x, int len)
{
	int sign, temp;

	sign = (x >> (len-1)) & 1;
	temp = sign_unext(x, len-1);
	return (temp << 1) | sign;
}
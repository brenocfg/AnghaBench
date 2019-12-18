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
struct rbsp {int dummy; } ;

/* Variables and functions */
 int rbsp_read_bit (struct rbsp*) ; 

__attribute__((used)) static int __rbsp_read_bit(struct rbsp *rbsp, int *value)
{
	int tmp = rbsp_read_bit(rbsp);

	if (tmp < 0)
		return tmp;
	*value = tmp;

	return 0;
}
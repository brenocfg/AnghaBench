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
struct talitos_ptr {int /*<<< orphan*/  len; int /*<<< orphan*/  len1; } ;

/* Variables and functions */
 unsigned short be16_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned short from_talitos_ptr_len(struct talitos_ptr *ptr,
					   bool is_sec1)
{
	if (is_sec1)
		return be16_to_cpu(ptr->len1);
	else
		return be16_to_cpu(ptr->len);
}
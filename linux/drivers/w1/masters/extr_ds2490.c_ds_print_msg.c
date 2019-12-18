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
 int /*<<< orphan*/  pr_info (char*,unsigned char*,unsigned char) ; 

__attribute__((used)) static inline void ds_print_msg(unsigned char *buf, unsigned char *str, int off)
{
	pr_info("%45s: %8x\n", str, buf[off]);
}
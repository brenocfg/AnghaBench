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
 int /*<<< orphan*/  pr_cont (char*,char const*) ; 
 int /*<<< orphan*/  pr_info (char*,char const*) ; 

__attribute__((used)) static inline void write_to_printk(void *ctx, const char *str, size_t len,
				   bool cont)
{
	if (cont)
		pr_cont("%s", str);
	else
		pr_info("%s", str);
}
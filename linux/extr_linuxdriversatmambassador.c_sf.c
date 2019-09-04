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
 int /*<<< orphan*/  KERN_ERR ; 
 int /*<<< orphan*/  PRINTK (int /*<<< orphan*/ ,char*,char const*) ; 

__attribute__((used)) static inline void sf (const char * msg)
{
	PRINTK (KERN_ERR, "self-test failed: %s", msg);
}
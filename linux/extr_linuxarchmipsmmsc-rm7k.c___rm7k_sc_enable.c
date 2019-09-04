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
 int /*<<< orphan*/  CKSEG0ADDR (int) ; 
 int /*<<< orphan*/  Index_Store_Tag_SD ; 
 int /*<<< orphan*/  RM7K_CONF_SE ; 
 int /*<<< orphan*/  cache_op (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ sc_lsize ; 
 int scache_size ; 
 int /*<<< orphan*/  set_c0_config (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_c0_taghi (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_c0_taglo (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void __rm7k_sc_enable(void)
{
	int i;

	set_c0_config(RM7K_CONF_SE);

	write_c0_taglo(0);
	write_c0_taghi(0);

	for (i = 0; i < scache_size; i += sc_lsize)
		cache_op(Index_Store_Tag_SD, CKSEG0ADDR(i));
}
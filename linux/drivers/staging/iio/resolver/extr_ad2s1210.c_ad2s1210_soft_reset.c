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
struct ad2s1210_state {int dummy; } ;

/* Variables and functions */
 int AD2S1210_REG_SOFT_RESET ; 
 int ad2s1210_config_write (struct ad2s1210_state*,int) ; 

__attribute__((used)) static inline int ad2s1210_soft_reset(struct ad2s1210_state *st)
{
	int ret;

	ret = ad2s1210_config_write(st, AD2S1210_REG_SOFT_RESET);
	if (ret < 0)
		return ret;

	return ad2s1210_config_write(st, 0x0);
}
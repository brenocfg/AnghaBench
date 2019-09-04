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
typedef  int /*<<< orphan*/  u32 ;
struct cobalt {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  COBALT_SYS_STAT_BASE ; 
 int /*<<< orphan*/  cobalt_read_bar1 (struct cobalt*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline u32 cobalt_g_sysstat(struct cobalt *cobalt)
{
	return cobalt_read_bar1(cobalt, COBALT_SYS_STAT_BASE);
}
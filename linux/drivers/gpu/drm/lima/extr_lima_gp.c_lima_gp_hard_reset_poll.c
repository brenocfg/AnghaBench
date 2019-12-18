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
struct lima_ip {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  LIMA_GP_PERF_CNT_0_LIMIT ; 
 int gp_read (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gp_write (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int lima_gp_hard_reset_poll(struct lima_ip *ip)
{
	gp_write(LIMA_GP_PERF_CNT_0_LIMIT, 0xC01A0000);
	return gp_read(LIMA_GP_PERF_CNT_0_LIMIT) == 0xC01A0000;
}
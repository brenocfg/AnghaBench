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
struct s_smc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  FM_A (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FM_TSYNC ; 
 int /*<<< orphan*/  outpw (int /*<<< orphan*/ ,unsigned int) ; 

void set_formac_tsync(struct s_smc *smc, long sync_bw)
{
	outpw(FM_A(FM_TSYNC),(unsigned int) (((-sync_bw) >> 5) & 0xffff) ) ;
}
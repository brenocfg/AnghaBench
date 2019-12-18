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
struct petp {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  F_IP_CSUM ; 
 int /*<<< orphan*/  set_csum_offload (struct petp*,int /*<<< orphan*/ ,int) ; 

void t1_tp_set_ip_checksum_offload(struct petp *tp, int enable)
{
	set_csum_offload(tp, F_IP_CSUM, enable);
}
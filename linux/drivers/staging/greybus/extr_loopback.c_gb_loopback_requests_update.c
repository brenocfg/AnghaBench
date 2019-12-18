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
typedef  int u64 ;
typedef  int /*<<< orphan*/  u32 ;
struct gb_loopback {int requests_completed; int /*<<< orphan*/  requests_per_second; } ;

/* Variables and functions */
 int USEC_PER_SEC ; 
 int /*<<< orphan*/  gb_loopback_update_stats_window (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void gb_loopback_requests_update(struct gb_loopback *gb, u32 latency)
{
	u64 req = gb->requests_completed * USEC_PER_SEC;

	gb_loopback_update_stats_window(&gb->requests_per_second, req, latency);
}
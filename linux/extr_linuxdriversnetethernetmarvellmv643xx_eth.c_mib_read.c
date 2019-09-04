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
struct mv643xx_eth_private {int /*<<< orphan*/  port_num; } ;

/* Variables and functions */
 scalar_t__ MIB_COUNTERS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rdl (struct mv643xx_eth_private*,scalar_t__) ; 

__attribute__((used)) static inline u32 mib_read(struct mv643xx_eth_private *mp, int offset)
{
	return rdl(mp, MIB_COUNTERS(mp->port_num) + offset);
}
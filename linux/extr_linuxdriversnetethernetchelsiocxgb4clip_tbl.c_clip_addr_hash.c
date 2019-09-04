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
typedef  scalar_t__ u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct clip_tbl {int dummy; } ;

/* Variables and functions */
 unsigned int ipv4_clip_hash (struct clip_tbl*,int /*<<< orphan*/  const*) ; 
 unsigned int ipv6_clip_hash (struct clip_tbl*,int /*<<< orphan*/  const*) ; 

__attribute__((used)) static unsigned int clip_addr_hash(struct clip_tbl *ctbl, const u32 *addr,
				   u8 v6)
{
	return v6 ? ipv6_clip_hash(ctbl, addr) :
			ipv4_clip_hash(ctbl, addr);
}
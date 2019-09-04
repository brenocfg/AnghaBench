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
struct etnaviv_cmdbuf {int /*<<< orphan*/  user_size; } ;

/* Variables and functions */
 int /*<<< orphan*/  ALIGN (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  OUT (struct etnaviv_cmdbuf*,int) ; 
 int VIV_FE_STALL_HEADER_OP_STALL ; 
 int VIV_FE_STALL_TOKEN_FROM (int /*<<< orphan*/ ) ; 
 int VIV_FE_STALL_TOKEN_TO (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void CMD_STALL(struct etnaviv_cmdbuf *buffer,
	u32 from, u32 to)
{
	buffer->user_size = ALIGN(buffer->user_size, 8);

	OUT(buffer, VIV_FE_STALL_HEADER_OP_STALL);
	OUT(buffer, VIV_FE_STALL_TOKEN_FROM(from) | VIV_FE_STALL_TOKEN_TO(to));
}
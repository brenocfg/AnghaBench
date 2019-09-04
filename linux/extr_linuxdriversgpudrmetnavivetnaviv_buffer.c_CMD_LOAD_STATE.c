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
typedef  int u32 ;
struct etnaviv_cmdbuf {int /*<<< orphan*/  user_size; } ;

/* Variables and functions */
 int /*<<< orphan*/  ALIGN (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  OUT (struct etnaviv_cmdbuf*,int) ; 
 int VIV_FE_LOAD_STATE_HEADER_COUNT (int) ; 
 int VIV_FE_LOAD_STATE_HEADER_OFFSET (int) ; 
 int VIV_FE_LOAD_STATE_HEADER_OFFSET__SHR ; 
 int VIV_FE_LOAD_STATE_HEADER_OP_LOAD_STATE ; 

__attribute__((used)) static inline void CMD_LOAD_STATE(struct etnaviv_cmdbuf *buffer,
	u32 reg, u32 value)
{
	u32 index = reg >> VIV_FE_LOAD_STATE_HEADER_OFFSET__SHR;

	buffer->user_size = ALIGN(buffer->user_size, 8);

	/* write a register via cmd stream */
	OUT(buffer, VIV_FE_LOAD_STATE_HEADER_OP_LOAD_STATE |
		    VIV_FE_LOAD_STATE_HEADER_COUNT(1) |
		    VIV_FE_LOAD_STATE_HEADER_OFFSET(index));
	OUT(buffer, value);
}
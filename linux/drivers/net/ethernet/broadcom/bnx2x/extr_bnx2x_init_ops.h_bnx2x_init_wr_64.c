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
typedef  int /*<<< orphan*/  u64 ;
typedef  int u32 ;
struct bnx2x {int dummy; } ;

/* Variables and functions */
 int FW_BUF_SIZE ; 
 scalar_t__ GUNZIP_BUF (struct bnx2x*) ; 
 int /*<<< orphan*/  HILO_U64 (int const,int const) ; 
 int /*<<< orphan*/  bnx2x_write_big_buf_wb (struct bnx2x*,int,int) ; 
 int min (int,int) ; 

__attribute__((used)) static void bnx2x_init_wr_64(struct bnx2x *bp, u32 addr,
			     const u32 *data, u32 len64)
{
	u32 buf_len32 = FW_BUF_SIZE/4;
	u32 len = len64*2;
	u64 data64 = 0;
	u32 i;

	/* 64 bit value is in a blob: first low DWORD, then high DWORD */
	data64 = HILO_U64((*(data + 1)), (*data));

	len64 = min((u32)(FW_BUF_SIZE/8), len64);
	for (i = 0; i < len64; i++) {
		u64 *pdata = ((u64 *)(GUNZIP_BUF(bp))) + i;

		*pdata = data64;
	}

	for (i = 0; i < len; i += buf_len32) {
		u32 cur_len = min(buf_len32, len - i);

		bnx2x_write_big_buf_wb(bp, addr + i*4, cur_len);
	}
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
typedef  int u16 ;
struct TYPE_2__ {scalar_t__ va; } ;
struct i40iw_puda_buf {TYPE_1__ mem; } ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (void*,void*,int) ; 

__attribute__((used)) static void i40iw_ieq_copy_to_txbuf(struct i40iw_puda_buf *buf,
				    struct i40iw_puda_buf *txbuf,
				    u16 buf_offset, u32 txbuf_offset,
				    u32 length)
{
	void *mem1 = (u8 *)buf->mem.va + buf_offset;
	void *mem2 = (u8 *)txbuf->mem.va + txbuf_offset;

	memcpy(mem2, mem1, length);
}
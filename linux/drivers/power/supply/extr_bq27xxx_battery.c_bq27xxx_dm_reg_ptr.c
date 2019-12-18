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
typedef  int /*<<< orphan*/  u16 ;
struct bq27xxx_dm_reg {scalar_t__ subclass_id; int offset; } ;
struct bq27xxx_dm_buf {scalar_t__ class; int block; scalar_t__ data; } ;

/* Variables and functions */
 int BQ27XXX_DM_SZ ; 

__attribute__((used)) static inline u16 *bq27xxx_dm_reg_ptr(struct bq27xxx_dm_buf *buf,
				      struct bq27xxx_dm_reg *reg)
{
	if (buf->class == reg->subclass_id &&
	    buf->block == reg->offset / BQ27XXX_DM_SZ)
		return (u16 *) (buf->data + reg->offset % BQ27XXX_DM_SZ);

	return NULL;
}
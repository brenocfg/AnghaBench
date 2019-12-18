#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int u64 ;
struct dm_verity {int data_dev_block_bits; TYPE_2__* fec; TYPE_1__* data_dev; } ;
struct dm_buffer {int dummy; } ;
struct TYPE_4__ {int roots; scalar_t__ start; int /*<<< orphan*/  bufio; } ;
struct TYPE_3__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMERR (char*,int /*<<< orphan*/ ,unsigned long long,unsigned long long,int /*<<< orphan*/ ) ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PTR_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * dm_bufio_read (int /*<<< orphan*/ ,scalar_t__,struct dm_buffer**) ; 

__attribute__((used)) static u8 *fec_read_parity(struct dm_verity *v, u64 rsb, int index,
			   unsigned *offset, struct dm_buffer **buf)
{
	u64 position, block;
	u8 *res;

	position = (index + rsb) * v->fec->roots;
	block = position >> v->data_dev_block_bits;
	*offset = (unsigned)(position - (block << v->data_dev_block_bits));

	res = dm_bufio_read(v->fec->bufio, v->fec->start + block, buf);
	if (IS_ERR(res)) {
		DMERR("%s: FEC %llu: parity read failed (block %llu): %ld",
		      v->data_dev->name, (unsigned long long)rsb,
		      (unsigned long long)(v->fec->start + block),
		      PTR_ERR(res));
		*buf = NULL;
	}

	return res;
}
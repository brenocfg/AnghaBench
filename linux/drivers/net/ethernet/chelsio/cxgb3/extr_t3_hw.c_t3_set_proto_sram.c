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
typedef  int /*<<< orphan*/  u8 ;
struct adapter {int dummy; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int /*<<< orphan*/  A_TP_EMBED_OP_FIELD0 ; 
 int /*<<< orphan*/  A_TP_EMBED_OP_FIELD1 ; 
 int /*<<< orphan*/  A_TP_EMBED_OP_FIELD2 ; 
 int /*<<< orphan*/  A_TP_EMBED_OP_FIELD3 ; 
 int /*<<< orphan*/  A_TP_EMBED_OP_FIELD4 ; 
 int /*<<< orphan*/  A_TP_EMBED_OP_FIELD5 ; 
 int EIO ; 
 int PROTO_SRAM_LINES ; 
 int be32_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ t3_wait_op_done (struct adapter*,int /*<<< orphan*/ ,int,int,int,int) ; 
 int /*<<< orphan*/  t3_write_reg (struct adapter*,int /*<<< orphan*/ ,int) ; 

int t3_set_proto_sram(struct adapter *adap, const u8 *data)
{
	int i;
	const __be32 *buf = (const __be32 *)data;

	for (i = 0; i < PROTO_SRAM_LINES; i++) {
		t3_write_reg(adap, A_TP_EMBED_OP_FIELD5, be32_to_cpu(*buf++));
		t3_write_reg(adap, A_TP_EMBED_OP_FIELD4, be32_to_cpu(*buf++));
		t3_write_reg(adap, A_TP_EMBED_OP_FIELD3, be32_to_cpu(*buf++));
		t3_write_reg(adap, A_TP_EMBED_OP_FIELD2, be32_to_cpu(*buf++));
		t3_write_reg(adap, A_TP_EMBED_OP_FIELD1, be32_to_cpu(*buf++));

		t3_write_reg(adap, A_TP_EMBED_OP_FIELD0, i << 1 | 1 << 31);
		if (t3_wait_op_done(adap, A_TP_EMBED_OP_FIELD0, 1, 1, 5, 1))
			return -EIO;
	}
	t3_write_reg(adap, A_TP_EMBED_OP_FIELD0, 0);

	return 0;
}
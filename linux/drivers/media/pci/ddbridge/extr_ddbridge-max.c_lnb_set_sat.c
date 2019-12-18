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
struct dvb_diseqc_master_cmd {int* msg; int msg_len; } ;
struct ddb {int dummy; } ;

/* Variables and functions */
 int lnb_send_diseqc (struct ddb*,int,int,struct dvb_diseqc_master_cmd*) ; 

__attribute__((used)) static int lnb_set_sat(struct ddb *dev, u32 link, u32 input, u32 sat, u32 band,
		       u32 hor)
{
	struct dvb_diseqc_master_cmd cmd = {
		.msg = {0xe0, 0x10, 0x38, 0xf0, 0x00, 0x00},
		.msg_len = 4
	};
	cmd.msg[3] = 0xf0 | (((sat << 2) & 0x0c) | (band ? 1 : 0) |
		(hor ? 2 : 0));
	return lnb_send_diseqc(dev, link, input, &cmd);
}
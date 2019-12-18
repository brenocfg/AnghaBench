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
struct cnic_dev {int dummy; } ;

/* Variables and functions */
 int CTX_SIZE ; 
 int /*<<< orphan*/  GET_CID_ADDR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cnic_ctx_wr (struct cnic_dev*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void cnic_init_context(struct cnic_dev *dev, u32 cid)
{
	u32 cid_addr;
	int i;

	cid_addr = GET_CID_ADDR(cid);

	for (i = 0; i < CTX_SIZE; i += 4)
		cnic_ctx_wr(dev, cid_addr, i, 0);
}
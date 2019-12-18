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
struct TYPE_3__ {int /*<<< orphan*/  length; } ;
struct TYPE_4__ {TYPE_1__ header; } ;
struct redrat3_dev {unsigned int bytes_read; TYPE_2__ irdata; int /*<<< orphan*/  dev; int /*<<< orphan*/  bulk_in_buf; } ;

/* Variables and functions */
 int /*<<< orphan*/  be16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  memcpy (void*,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static void redrat3_read_packet_continue(struct redrat3_dev *rr3, unsigned len)
{
	void *irdata = &rr3->irdata;

	if (len + rr3->bytes_read > sizeof(rr3->irdata)) {
		dev_warn(rr3->dev, "too much data for packet\n");
		rr3->bytes_read = 0;
		return;
	}

	memcpy(irdata + rr3->bytes_read, rr3->bulk_in_buf, len);

	rr3->bytes_read += len;
	dev_dbg(rr3->dev, "bytes_read %d, pktlen %d\n", rr3->bytes_read,
				 be16_to_cpu(rr3->irdata.header.length));
}
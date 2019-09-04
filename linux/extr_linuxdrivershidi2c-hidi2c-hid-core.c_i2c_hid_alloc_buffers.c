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
typedef  union command {int dummy; } command ;
struct i2c_hid {size_t bufsize; void* cmdbuf; void* argsbuf; void* rawbuf; void* inbuf; } ;
typedef  int /*<<< orphan*/  __u8 ;
typedef  int /*<<< orphan*/  __u16 ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  i2c_hid_free_buffers (struct i2c_hid*) ; 
 void* kzalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int i2c_hid_alloc_buffers(struct i2c_hid *ihid, size_t report_size)
{
	/* the worst case is computed from the set_report command with a
	 * reportID > 15 and the maximum report length */
	int args_len = sizeof(__u8) + /* ReportID */
		       sizeof(__u8) + /* optional ReportID byte */
		       sizeof(__u16) + /* data register */
		       sizeof(__u16) + /* size of the report */
		       report_size; /* report */

	ihid->inbuf = kzalloc(report_size, GFP_KERNEL);
	ihid->rawbuf = kzalloc(report_size, GFP_KERNEL);
	ihid->argsbuf = kzalloc(args_len, GFP_KERNEL);
	ihid->cmdbuf = kzalloc(sizeof(union command) + args_len, GFP_KERNEL);

	if (!ihid->inbuf || !ihid->rawbuf || !ihid->argsbuf || !ihid->cmdbuf) {
		i2c_hid_free_buffers(ihid);
		return -ENOMEM;
	}

	ihid->bufsize = report_size;

	return 0;
}
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
typedef  scalar_t__ u32 ;
struct gb_loopback_transfer_response {int dummy; } ;
struct gb_loopback_transfer_request {int /*<<< orphan*/  len; int /*<<< orphan*/  data; } ;
struct gb_loopback {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GB_LOOPBACK_TYPE_TRANSFER ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  cpu_to_le32 (scalar_t__) ; 
 int gb_loopback_async_operation (struct gb_loopback*,int /*<<< orphan*/ ,struct gb_loopback_transfer_request*,scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gb_loopback_async_transfer_complete ; 
 int /*<<< orphan*/  kfree (struct gb_loopback_transfer_request*) ; 
 struct gb_loopback_transfer_request* kmalloc (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int,scalar_t__) ; 

__attribute__((used)) static int gb_loopback_async_transfer(struct gb_loopback *gb, u32 len)
{
	struct gb_loopback_transfer_request *request;
	int retval, response_len;

	request = kmalloc(len + sizeof(*request), GFP_KERNEL);
	if (!request)
		return -ENOMEM;

	memset(request->data, 0x5A, len);

	request->len = cpu_to_le32(len);
	response_len = sizeof(struct gb_loopback_transfer_response);
	retval = gb_loopback_async_operation(gb, GB_LOOPBACK_TYPE_TRANSFER,
					     request, len + sizeof(*request),
					     len + response_len,
					     gb_loopback_async_transfer_complete);
	if (retval)
		goto gb_error;

gb_error:
	kfree(request);
	return retval;
}
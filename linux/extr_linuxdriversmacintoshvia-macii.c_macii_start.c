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
struct adb_request {int* data; } ;

/* Variables and functions */
 size_t ACR ; 
 size_t B ; 
 int /*<<< orphan*/  BUG_ON (int) ; 
 size_t SR ; 
 int SR_OUT ; 
 int ST_CMD ; 
 int ST_MASK ; 
 int command_byte ; 
 struct adb_request* current_req ; 
 int data_index ; 
 scalar_t__ idle ; 
 scalar_t__ macii_state ; 
 scalar_t__ sending ; 
 int* via ; 

__attribute__((used)) static void macii_start(void)
{
	struct adb_request *req;

	req = current_req;

	BUG_ON(req == NULL);

	BUG_ON(macii_state != idle);

	/* Now send it. Be careful though, that first byte of the request
	 * is actually ADB_PACKET; the real data begins at index 1!
	 * And req->nbytes is the number of bytes of real data plus one.
	 */

	/* store command byte */
	command_byte = req->data[1];
	/* Output mode */
	via[ACR] |= SR_OUT;
	/* Load data */
	via[SR] = req->data[1];
	/* set ADB state to 'command' */
	via[B] = (via[B] & ~ST_MASK) | ST_CMD;

	macii_state = sending;
	data_index = 2;
}
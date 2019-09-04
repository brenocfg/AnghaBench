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
struct transaction_callback_data {int rcode; int /*<<< orphan*/  done; int /*<<< orphan*/  payload; } ;
struct fw_card {int dummy; } ;

/* Variables and functions */
 int RCODE_COMPLETE ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,void*,size_t) ; 

__attribute__((used)) static void transaction_callback(struct fw_card *card, int rcode,
				 void *payload, size_t length, void *data)
{
	struct transaction_callback_data *d = data;

	if (rcode == RCODE_COMPLETE)
		memcpy(d->payload, payload, length);
	d->rcode = rcode;
	complete(&d->done);
}
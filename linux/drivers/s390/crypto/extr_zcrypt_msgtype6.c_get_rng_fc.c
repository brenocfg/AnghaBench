#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct response_type {int /*<<< orphan*/  type; } ;
struct ap_message {int /*<<< orphan*/  private; scalar_t__ psmid; int /*<<< orphan*/  receive; int /*<<< orphan*/  message; } ;
typedef  int /*<<< orphan*/  resp_type ;
struct TYPE_2__ {scalar_t__ pid; } ;

/* Variables and functions */
 int /*<<< orphan*/  CEXXC_RESPONSE_TYPE_XCRB ; 
 unsigned int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int HWRNG ; 
 int /*<<< orphan*/  MSGTYPE06_MAX_MSG_SIZE ; 
 int /*<<< orphan*/  ZCRYPT_RNG_BUFFER_SIZE ; 
 scalar_t__ atomic_inc_return (int /*<<< orphan*/ *) ; 
 TYPE_1__* current ; 
 int /*<<< orphan*/  kmalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kmemdup (struct response_type*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rng_type6CPRB_msgX (struct ap_message*,int /*<<< orphan*/ ,unsigned int*) ; 
 int /*<<< orphan*/  zcrypt_msgtype6_receive ; 
 int /*<<< orphan*/  zcrypt_step ; 

unsigned int get_rng_fc(struct ap_message *ap_msg, int *func_code,
						   unsigned int *domain)
{
	struct response_type resp_type = {
		.type = CEXXC_RESPONSE_TYPE_XCRB,
	};

	ap_msg->message = kmalloc(MSGTYPE06_MAX_MSG_SIZE, GFP_KERNEL);
	if (!ap_msg->message)
		return -ENOMEM;
	ap_msg->receive = zcrypt_msgtype6_receive;
	ap_msg->psmid = (((unsigned long long) current->pid) << 32) +
				atomic_inc_return(&zcrypt_step);
	ap_msg->private = kmemdup(&resp_type, sizeof(resp_type), GFP_KERNEL);
	if (!ap_msg->private)
		return -ENOMEM;

	rng_type6CPRB_msgX(ap_msg, ZCRYPT_RNG_BUFFER_SIZE, domain);

	*func_code = HWRNG;
	return 0;
}
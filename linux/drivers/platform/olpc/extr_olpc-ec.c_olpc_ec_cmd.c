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
typedef  int /*<<< orphan*/  u8 ;
struct olpc_ec_priv {int suspended; } ;
struct ec_cmd_desc {size_t inlen; size_t outlen; int err; int /*<<< orphan*/  finished; int /*<<< orphan*/ * outbuf; int /*<<< orphan*/ * inbuf; int /*<<< orphan*/  cmd; } ;
struct TYPE_2__ {int /*<<< orphan*/  ec_cmd; } ;

/* Variables and functions */
 int EBUSY ; 
 int ENODEV ; 
 int ENOMEM ; 
 int EPROBE_DEFER ; 
 scalar_t__ WARN_ON (int) ; 
 TYPE_1__* ec_driver ; 
 struct olpc_ec_priv* ec_priv ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  might_sleep () ; 
 int /*<<< orphan*/  queue_ec_descriptor (struct ec_cmd_desc*,struct olpc_ec_priv*) ; 
 int /*<<< orphan*/  wait_for_completion (int /*<<< orphan*/ *) ; 

int olpc_ec_cmd(u8 cmd, u8 *inbuf, size_t inlen, u8 *outbuf, size_t outlen)
{
	struct olpc_ec_priv *ec = ec_priv;
	struct ec_cmd_desc desc;

	/* Driver not yet registered. */
	if (!ec_driver)
		return -EPROBE_DEFER;

	if (WARN_ON(!ec_driver->ec_cmd))
		return -ENODEV;

	if (!ec)
		return -ENOMEM;

	/* Suspending in the middle of a command hoses things really badly */
	if (WARN_ON(ec->suspended))
		return -EBUSY;

	might_sleep();

	desc.cmd = cmd;
	desc.inbuf = inbuf;
	desc.outbuf = outbuf;
	desc.inlen = inlen;
	desc.outlen = outlen;
	desc.err = 0;
	init_completion(&desc.finished);

	queue_ec_descriptor(&desc, ec);

	/* Timeouts must be handled in the platform-specific EC hook */
	wait_for_completion(&desc.finished);

	/* The worker thread dequeues the cmd; no need to do anything here */
	return desc.err;
}
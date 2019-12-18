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
struct siox_master {int active; int /*<<< orphan*/  poll_thread; int /*<<< orphan*/  buf; scalar_t__ getbuf_len; scalar_t__ setbuf_len; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  wake_up_process (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int __siox_start(struct siox_master *smaster)
{
	if (!(smaster->setbuf_len + smaster->getbuf_len))
		return -ENODEV;

	if (!smaster->buf)
		return -ENOMEM;

	if (smaster->active)
		return 0;

	smaster->active = 1;
	wake_up_process(smaster->poll_thread);

	return 1;
}
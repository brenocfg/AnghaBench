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
struct usdhi6_host {int /*<<< orphan*/  wait; } ;

/* Variables and functions */
 int /*<<< orphan*/  USDHI6_WAIT_FOR_DATA_END ; 
 int usdhi6_blk_write (struct usdhi6_host*) ; 
 int /*<<< orphan*/  usdhi6_sg_unmap (struct usdhi6_host*,int) ; 

__attribute__((used)) static bool usdhi6_write_block(struct usdhi6_host *host)
{
	int ret = usdhi6_blk_write(host);

	/* See comment in usdhi6_read_block() */
	usdhi6_sg_unmap(host, true);

	if (ret < 0)
		return false;

	host->wait = USDHI6_WAIT_FOR_DATA_END;
	return true;
}